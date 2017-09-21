#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QLabel *warning;
    QLabel *config;
    QDialog *window;
    QTcpSocket *client_login;
    QString account;

private:
    Ui::MainWindow *ui;

    private slots:
    void on_login_button_clicked();
    void on_register_button_clicked();
};


#endif // MAINWINDOW_H
