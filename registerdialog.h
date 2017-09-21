#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

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
class registerdialog;
}

class registerdialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerdialog(QWidget *parent = 0);
    ~registerdialog();

    QTcpSocket *client;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::registerdialog *ui;
};

#endif // REGISTERDIALOG_H
