#ifndef NETACCESS_H
#define NETACCESS_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QtNetwork>

class netaccess : public QObject
{
    Q_OBJECT
public:
    explicit netaccess(QObject *parent = 0);

signals:

public slots:
    int init(int port, QString host);
    bool clientConnect();
    bool clientDisconnect();

private:
    bool sockStatus;
    QTcpSocket *sockNet;
    QTcpServer *servNet;

};

#endif // NETACCESS_H
