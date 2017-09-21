#include "downloads.h"
#include "ui_downloads.h"
#include "mainwindow.h"
#include  "help.h"
#include <unistd.h>
#include "share.h"
#include <QThread>
#include <QProcess>
downloads::downloads(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::downloads)
{
    ui->setupUi(this);
    this->setWindowTitle("下载或上传");
}

downloads::~downloads()
{
    delete ui;
}

void downloads::on_uploading_clicked()  //点击文件按钮
{
    filename = QFileDialog::getOpenFileName(this,"选择一个文件");
    ui->upload_path->setText(filename);
    ui->download_path->clear();
}

void downloads::set_test(QString info_name, QString list){  //将主窗口的数据传输过来
    file_folder = info_name;
    ui->textEdit->setText(list);
    ui->name->setText(info_name);
    ui->textEdit->setText("该文件夹中包含的文件有："+list);
}

void downloads::set_client(QTcpSocket *client_flag){
   sender = client_flag;
   receiver = client_flag;
   deleter = client_flag;
}


void downloads::on_pushButton_3_clicked()  //点击上传按钮
{
    int split_count;      //将文件的“／”分割出来的计数器
    QString temp;        //用于传输数据途中的中间量
    QStringList pyfilename_temp;  //用于取出文件名
    QString pyfilename;     //python 服务器端存储的文件名
    QString Md5;
    QString confirm_Md5;
    QByteArray confirm_Md5_server;
    QString Md5_filesize;
    //sender->flush();
    //usleep(500000);

    QFile sendfile(filename);

    if (! sendfile.open(QFile::ReadOnly)){
            return;
       }

    QString size;      //文件大小string类型来表示，用于之后的字节转换
    size = QString::number(sendfile.size());
    qDebug()<<"文件大小为："<<size;

    QByteArray realfile = sendfile.readAll();
    QByteArray bArray = QCryptographicHash::hash(realfile,QCryptographicHash::Md5); //获取该文件的Md5码
    Md5 = QString(bArray.toHex()).toUpper();
    qDebug()<<"Md5码为："<<Md5;
    Md5_filesize = Md5+"#"+size;

    pyfilename_temp = filename.split("/");
    split_count = (filename.split("/").size() - 1);
    pyfilename = pyfilename_temp[split_count];

    temp = "s#"+pyfilename+"#"+file_folder+"#"+Md5_filesize;    //发送文件标签包括账户名字
    //qDebug()<<"要传输的信息为："<<temp;
    QByteArray flag = temp.toLatin1();
    flag = flag.toBase64();      //Base64加密
    qDebug()<<"Base64加密之后的信息为："<<flag;

    sender->write(flag);        //发送上传文件的信息包括要传输的文件名字
    sender->waitForBytesWritten();

    sender->waitForReadyRead();
    confirm_Md5_server = sender->read(1024);  //服务器那边发送来md5的确认结果
    confirm_Md5 = confirm_Md5_server.data();
    qDebug()<<"confirm_Md5 is:"<<confirm_Md5;

    if (confirm_Md5 == "exist"){
       QMessageBox::information(this,"提示","上传成功!");
    }

    else if (confirm_Md5 == "not exist"){
        qDebug()<<"进入该循环！";
        QString progress;
        QByteArray server_progress;
        sender->write(realfile);     //传输实际文件
        sender->waitForBytesWritten();
        sender->waitForReadyRead();
        server_progress = sender->read(1024);  //在服务器那边传输完成后会发来"done"
        progress = server_progress.data();
        qDebug()<<"progress is :"<<progress;
        if (progress == "done"){
         QMessageBox::information(this,"提示","上传成功!");
        }
        else  {
         QMessageBox::information(this,"提示","上传失败!");
        }

    }
    else {
       QMessageBox::information(this,"提示","上传失败!");
    }
    sendfile.close();

}

void downloads::on_pushButton_clicked()  //共享按钮
{
    share *share_dialog = new share(this);
    share_dialog->set_share_name(sender);
    share_dialog->set_sender_name(file_folder);
    share_dialog->exec();
}

void downloads::on_pushButton_4_clicked()  //帮助按钮
{
    help *help_dialog =new help(this);
    help_dialog->exec();
}

void downloads::on_download_clicked()  //下载按钮
{
    QString downloads_file_path = QFileDialog::getExistingDirectory(this,"选择一个文件目录:");
    QString write_file_flag;
    QString downloads_file_name;
    downloads_file_name = ui->download_path->text();
    QString yourfile = downloads_file_name;
    downloads_file_name ="d#"+downloads_file_name+"#"+file_folder;  //将文件名以及包含这个文件的文件夹的名字传送过去
    QByteArray file = downloads_file_name.toLatin1();
    file = file.toBase64();
    receiver->write(file);
    receiver->waitForBytesWritten();

    QFile receive_file_path(downloads_file_path+"/"+yourfile);
    receive_file_path.open(QIODevice::ReadWrite);

    while (true) {
        receiver->waitForReadyRead();
        QByteArray receive_file = receiver->read(1024);
        QString receivefile2 = receive_file.data();
        //qDebug()<<"服务器发来的消息为："<<receivefile2;
         if (receivefile2 == "finish"){
             QMessageBox::information(this,"提示","下载完毕!");
             break;
            }
         receive_file_path.write(receive_file);
        }
    receive_file_path.close();


    /*QStringList args;
    args.append("/Users/WBLLY/WBL/Computer_Science/Computer_Network/python_code/recv.py");
    args.append(downloads_file_name);
    args.append(downloads_file_path+"/"+yourfile);
    QProcess::execute(QString("Python"),args);*/
}

void downloads::on_pushButton_2_clicked()  //删除按钮
{
    QString delete_file;
    QString flag;
    delete_file = ui->download_path->text();
    delete_file = "r#"+delete_file+"#"+file_folder;
    QByteArray delete_file_to_send = delete_file.toLatin1();
    delete_file_to_send = delete_file_to_send.toBase64();
    deleter->write(delete_file_to_send);
    deleter->waitForBytesWritten();
    deleter->waitForReadyRead();
    QByteArray foo = deleter->read(1024);
    flag = foo.data();
   if (flag == "ok")  //表示删除成功
         {QMessageBox::information(this,"提示","文件删除成功!");}
    else
         {QMessageBox::warning(this,"提示","文件删除失败!");}

}
