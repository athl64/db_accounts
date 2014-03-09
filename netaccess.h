#ifndef NETACCESS_H
#define NETACCESS_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>


class netaccess : public QObject
{
    Q_OBJECT
public:
    explicit netaccess(QObject *parent = 0);

signals:

public slots:
    int init(int port, QString host);
    bool clientConnected();
    bool clientDisconnected();
    bool readyRead();
    void writed(qint64 bytes);

private:
    bool sockStatus;
    QTcpSocket *sock;
};

#endif // NETACCESS_H
