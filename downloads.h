#ifndef DOWNLOADS_H
#define DOWNLOADS_H


#include <QLabel>
#include <QByteArray>
#include <QCryptographicHash>
#include <QPushButton>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QFile>
#include <QFileDialog>
#include <QThread>
#include <QMainWindow>
#include <QDialog>
#include <QtNetwork>
#include <QTcpSocket>
#include <QMessageBox>

namespace Ui {
class downloads;
}

class downloads : public QDialog
{
    Q_OBJECT

public:
    explicit downloads(QWidget *parent = 0);
    ~downloads();

public:
    void set_test(QString a,QString b);
    QString filename;  //文件路径和名称
    QTcpSocket *sender;
    QTcpSocket *receiver;
    QTcpSocket *deleter;
    QString file_folder;
    void set_client(QTcpSocket *client);

private slots:
    void on_uploading_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_download_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::downloads *ui;
};

#endif // DOWNLOADS_H
