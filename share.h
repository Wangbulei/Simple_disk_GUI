#ifndef SHARE_H
#define SHARE_H
#include <QDialog>
#include <QMainWindow>
#include <QtNetwork>
#include <QTcpSocket>
#include <QMessageBox>
#include <QLabel>
#include <QByteArray>
#include <QCryptographicHash>
#include <QPushButton>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QFile>
#include <QFileDialog>

namespace Ui {
class share;
}

class share : public QDialog
{
    Q_OBJECT

public:
    explicit share(QWidget *parent = 0);
    ~share();

 public:
    void set_share_name(QTcpSocket *client_name);
    void set_sender_name(QString ori_client);
    QString sender_name;
    QTcpSocket *share_sock;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::share *ui;
};

#endif // SHARE_H
