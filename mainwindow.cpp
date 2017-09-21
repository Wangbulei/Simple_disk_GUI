#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registerdialog.h"
#include "downloads.h"
#include "share.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->passwordline->setEchoMode(QLineEdit::Password);//当输入密码时，显示为*******
    this->setWindowTitle("BUG网盘");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_button_clicked()  //登陆按钮
{
   // QString account; // 定义在头文件里面，其它源函数要使用。
    QString passwd;
    QString confirm; //用于将账户信息发送过去
    QString temp,flag;    // 用于接受消息
    QMessageBox yes,no;  //登陆验证消息
    //account = new QString();
    account = ui->client_edit->text();
    passwd = ui->passwordline->text();
    confirm ="0#"+account+"?"+passwd; //处理数据的操作
    client_login = new QTcpSocket(this);
    client_login->connectToHost(QHostAddress("104.224.142.153"),10005);
    //client_login->connectToHost(QHostAddress("127.0.0.1"),12345);
    QByteArray confirmto = confirm.toLatin1();
    confirmto = confirmto.toBase64();
    client_login->write(confirmto);
    client_login->waitForBytesWritten();
    client_login->waitForReadyRead();
    temp = client_login->read(1024); //接受服务器验证消息
    //qDebug()<<temp;
        if (temp == "wrong") {
            no.setText("账号或密码错误！");
            no.exec();
            ui->passwordline->clear();  //清空密码栏
            ui->passwordline->setFocus();  //光标重置
        }

        else if (temp == "notwrong"){
            client_login->waitForReadyRead();
            flag = client_login->read(1024);   //接收服务器发送过来的文件夹中包含的文件。
            yes.setText("欢迎使用BUG网盘！");
            yes.exec();
            this->close();
            downloads *down_up = new downloads(this);
            down_up->set_test(account,flag);  //将主窗口接受的消息传递到下载文件窗口中
            down_up->set_client(client_login);
            down_up->exec();
        }
        else  {
            no.setText("账号或密码错误！");
            no.exec();
            ui->passwordline->clear();  //清空密码栏
            ui->passwordline->setFocus();  //光标重置
        }

}

void MainWindow::on_register_button_clicked()
{
    registerdialog *rigister_dialog=new registerdialog(this);
    rigister_dialog->exec();
}

