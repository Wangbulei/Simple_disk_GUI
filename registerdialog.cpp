#include "registerdialog.h"
#include "ui_registerdialog.h"

registerdialog::registerdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerdialog)
{
    ui->setupUi(this);
    ui->register_password->setEchoMode(QLineEdit::Password);//当输入密码时，显示为*******
    this->setWindowTitle("注册");
}

registerdialog::~registerdialog()
{
    delete ui;
}

void registerdialog::on_pushButton_clicked()  //注册按钮
{
   QString info;
   QString r_name;
   QString r_passwd;
   QString temp;
   QMessageBox warning;
   client = new QTcpSocket(this);
   client->connectToHost(QHostAddress("104.224.142.153"),10005);
   //client->connectToHost(QHostAddress("127.0.0.1"),12345);
   client->waitForConnected();
   r_name = ui->register_name->text();
   r_passwd = ui->register_password->text();
   info ="1#"+r_name+"?"+r_passwd;
   QByteArray infoto=info.toLatin1();
   infoto = infoto.toBase64();
   //info = QByteArray(info);
   client->write(infoto);
   client->waitForBytesWritten();
   client->waitForReadyRead();
   temp = client->read(1024);

   if  (temp == "wrong"){
       warning.setText("该账号已经被注册了！");
       warning.exec();
       ui->register_name->clear();
       ui->register_password->clear();
       ui->register_name->setFocus();
    }

    else if (temp == "yes"){
        warning.setText("注册成功！");
        warning.exec();
        this->close();
        client->abort();
    }
    else {
       warning.setText("该账号已经被注册了！");
       warning.exec();
       ui->register_name->clear();
       ui->register_password->clear();
       ui->register_name->setFocus();
   }

}

void registerdialog::on_pushButton_2_clicked()  //退出按钮
{
    this->close();
}
