#include "share.h"
#include "ui_share.h"
#include "mainwindow.h"
#include "downloads.h"

share::share(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::share)
{
    ui->setupUi(this);
    this->setWindowTitle("共享");
}

share::~share()
{
    delete ui;
}

void share::set_share_name(QTcpSocket *client_name){
    share_sock = client_name;
}

void share::set_sender_name(QString ori_client){
    sender_name = ori_client;
}


void share::on_pushButton_2_clicked()  //取消按钮
{
    this->close();
}

void share::on_pushButton_clicked()  //确定按钮
{
    QString file_name;
    QString share_user_name;
    QString send_file_info;
    QByteArray sock_info;
    QString check_info;
    QByteArray server_info;
    file_name = ui->file_name_edit->text();
    share_user_name = ui->user_name_edit->text();
    send_file_info = "b#"+file_name+"#"+share_user_name+"#"+sender_name;
    sock_info = send_file_info.toLatin1();
    sock_info = sock_info.toBase64();
    share_sock->write(sock_info);
    share_sock->waitForBytesWritten();
    share_sock->waitForReadyRead();
    server_info = share_sock->read(1024);
    check_info = server_info.data();
    //qDebug()<<check_info;
    if (check_info == "ok"){
        QMessageBox::information(this,"提示","分享成功！");
    }
    else if (check_info == "no"){
        QMessageBox::warning(this,"警告","没有该用户！");
    }

}
