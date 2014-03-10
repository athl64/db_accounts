#include "netaccess.h"

netaccess::netaccess(QObject *parent) :
    QObject(parent)
{
    qDebug() << "netaccess class initialised";
}

//single socket - get request
int netaccess::init(int port, QString host) {
    sock = new QTcpSocket(this);

    connect(sock,SIGNAL(connected()),this,SLOT(clientConnected()));
    connect(sock,SIGNAL(disconnected()),this,SLOT(clientDisconnected()));
    connect(sock,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(sock,SIGNAL(bytesWritten(qint64)),this,SLOT(writed(qint64)));

    sock->connectToHost(host,port);

    qDebug() << "connecting...";

    if(!sock->waitForConnected(1000)) {
        qDebug() << "shit...not error: " << sock->errorString();
    }

    return 0;
}

bool netaccess::clientConnected() {
    qDebug() << "sock connected";
    sock->write("GET / HTTP/1.0\r\n\r\n\r\n\r\n");
    sock->waitForBytesWritten(3000);
    return false;
}

bool netaccess::clientDisconnected() {
    qDebug() << "socket disconnected";
    return false;
}

bool netaccess::readyRead() {
    qDebug() << "trying to read something...";
    qDebug() << sock->readAll();
    return false;
}

void netaccess::writed(qint64 bytes) {
    qDebug() << "writed bytes: " << bytes;
    sock->waitForReadyRead(3000);
}

//server
void netaccess::servStart(int port) {
    serv = new QTcpServer(this);

    connect(serv,SIGNAL(newConnection()),this,SLOT(newConn()));

    if(!serv->listen(QHostAddress::Any,port)) {
        qDebug() << "server cannot start";
    } else {
        qDebug() << "server started to listen " << port << " port";
    }
    //not workng without it !!!
    //serv->waitForNewConnection(3000);
}

void netaccess::servStop() {
    qDebug() << "server stoped.";
}

void netaccess::newConn() {
    qDebug() << "we have new connection!";

    QTcpSocket *client = serv->nextPendingConnection();
    qDebug() << "request from new client: " << client->readAll();
    //client->waitForConnected(3000);
    //client->waitForReadyRead(3000);
    client->write("200 OK\r\n\r\n\r\n\r\n");
    client->flush();
    client->waitForBytesWritten(3000);
    client->close();
}
