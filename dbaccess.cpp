#include "dbaccess.h"

dbAccess::dbAccess()
{
}

dbAccess::~dbAccess()
{
    if(dbStatus) {
        db.close();
        dbStatus = false;
    }
}

int dbAccess::initialize(QString hostname, quint16 port, QString dbAlias, QString login, QString password)
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName(hostname);
    db.setPort(port);
    db.setDatabaseName(dbAlias);
    db.setUserName(login);
    db.setPassword(password);
    dbStatus = false;
    if(db.isOpenError()) {
        qDebug() << db.lastError() ;
    }
    return 1;
}

int dbAccess::dbOpen()
{
    if(db.open()) {
        dbStatus = true;
        qDebug() << "connected";
        return 1;
    } else {
        qDebug() << db.lastError();
        dbStatus = false;
        return -1;
    }
}

int dbAccess::dbClose()
{
    db.close();
    dbStatus = false;
    qDebug() << "disconnected";
    return 1;
}

QList<QString> dbAccess::getTitle()
{
    QList<QString> result;
    if(dbStatus) {
        request = QSqlQuery(db);
        request.exec("select Title from contacts");
        while(request.next()) {
            result.append(request.value(0).toString());
            qDebug() << "title request: " << request.value(0).toString();
        }
        return result;
    } else {
        qDebug() << "Database doesn't open";
    }
}

QList<base> dbAccess::getBody() {
    QList<base> result;
    int id = 0;
    QString title = "",
            attr = "",
            changed = "",
            added = "",
            modified = "";
    if(dbStatus) {
        request = QSqlQuery(db);
        request.exec("select ID, Title, Attributes, changedFiles, dateAdded, dateModified from contacts limit = 100");
        while(request.next()) {
            id = request.value(0).toInt();
            title = request.value(1).toString();
            attr = request.value(2).toString();
            changed = request.value(3).toString();
            added = request.value(4).toString();
            modified = request.value(5).toString();
            result.append( {id, title, attr, changed, added, modified} );
            qDebug() << "body request: " << QString::number(id) + title + attr + changed + added + modified ;
        }
        return result;
    } else {
        qDebug() << "Database doesn't open";
    }
}

int dbAccess::addNewContact(QString id, QString title, QString attr, QString changed, QString dateAdded, QString dateModifoed) {
    if(dbStatus) {
        request = QSqlQuery(db);
        int idNum = 0;
        QString idStr = "";
        if( (idNum = id.toInt()) >= 0) {
            idStr = id;
        }
        idStr = "";//temp for debug
        QString strVariables = "\"" + idStr + "\",\"" + title + "\",\"" + attr + "\",\"" + changed + "\",\"" + dateAdded + "\",\"" + dateModifoed + "\"";
        request.exec("insert into contacts (ID,Title, Attributes, changedFiles, dateAdded, dateModified) values(" + strVariables + ")");
        qDebug() << "error while insert" << db.lastError();
        return 1;
    }
}
