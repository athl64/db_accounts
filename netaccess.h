#ifndef NETACCESS_H
#define NETACCESS_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>
#include <QDebug>


class netaccess : public QObject
{
    Q_OBJECT
public:
    explicit netaccess(QObject *parent = 0);

signals:

public slots:
    //single connection - get request
    int init(int port, QString host);
    bool clientConnected();
    bool clientDisconnected();
    bool readyRead();
    void writed(qint64 bytes);
    //for server listener
    void servStart(int port);
    void servStop();
    void newConn();

private:
    QTcpSocket *sock;
    QTcpServer *serv;
};

#endif // NETACCESS_H
