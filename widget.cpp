#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpserver = new QTcpServer(this);
    tcpserver->listen(QHostAddress::Any, 8888);
    connect(tcpserver, &QTcpServer::newConnection, this, &Widget::ConnectToClient);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::ConnectToClient(){
    tcpsocket = tcpserver->nextPendingConnection();
    QString ip = tcpsocket->peerAddress().toString();
    quint16 port = tcpsocket->peerPort();
    ui->textEditRead->setText(QString("[%1:%2]连接成功").arg(ip).arg(port));
    connect(tcpsocket, &QTcpSocket::readyRead, this, &Widget::ReadInformation);
}

void Widget::ReadInformation(){
    QByteArray temp = tcpsocket->readAll();
    ui->textEditRead->append(temp);

}

void Widget::on_btnSend_clicked()
{
    QString str = ui->textEditWrite->toPlainText();
    tcpsocket->write(str.toUtf8().data());
}

void Widget::on_btnDisconnect_clicked()
{
    tcpsocket->write(QString("服务端请求断开").toUtf8().data());
    QString ip = tcpsocket->peerAddress().toString();
    quint16 port = tcpsocket->peerPort();
    ui->textEditRead->append(QString("[%1:%2]断开连接").arg(ip).arg(port));
    tcpsocket->disconnectFromHost();
    tcpsocket->close();
    tcpsocket = nullptr;
}
