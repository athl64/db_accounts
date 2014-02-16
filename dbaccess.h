#ifndef DBACCESS_H
#define DBACCESS_H

#include <QString>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "baseStruct.h"

class dbAccess
{
public:
    dbAccess();
    ~dbAccess();

private:
    QString hostname;
    qint16 port;
    QString dbAlias;
    QString login;
    QString password;

    QSqlDatabase db;
    QSqlQuery request;
    bool dbStatus;

public:
    int initialize(QString hostname, quint16 port, QString dbAlias, QString login, QString password);
    int dbOpen();
    int dbClose();
    QList<QString> getTitle();
    QList<key> getTitleID();
    QList<base> getBody();
    QList<base> getBodyByID(int id);
    int addNewContact(QString id, QString title, QString attr, QString changed);
    int gen_random_str(QString &strIN);
};

#endif // DBACCESS_H
