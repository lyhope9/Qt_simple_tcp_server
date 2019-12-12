#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void ConnectToClient();
    void ReadInformation();

private slots:
    void on_btnSend_clicked();

    void on_btnDisconnect_clicked();

private:
    Ui::Widget *ui;
    QTcpServer* tcpserver;
    QTcpSocket* tcpsocket;

};

#endif // WIDGET_H
