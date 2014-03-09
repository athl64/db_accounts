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
        qDebug() << "connected to DataBase";
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
    qDebug() << "disconnected from DataBase";
    return 1;
}

QList<QString> dbAccess::getTitle()
{
    QList<QString> result;
    if(dbStatus) {
        request = QSqlQuery(db);
        request.exec("select Title from contacts Order by Title ASC");
        while(request.next()) {
            result.append(request.value(0).toString());
            //qDebug() << "title request: " << request.value(0).toString();
        }
        return result;
    } else {
        qDebug() << "Database doesn't open";
    }
}

QList<key> dbAccess::getTitleID() {
    QList<key> result;
    if(dbStatus) {
        request = QSqlQuery(db);
        request.exec("select ID, Title from contacts Order by Title ASC");
        while(request.next()) {
            result.append({request.value(0).toInt(),request.value(1).toString()});
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
            //qDebug() << "body request: " << QString::number(id) + title + attr + changed + added + modified ;
        }
        return result;
    } else {
        qDebug() << "Database doesn't open";
    }
}

QList<base> dbAccess::getBodyByID(int id = -1) {
    QList<base> result;
    int ID = 0;
    QString title = "",
            attr = "",
            changed = "",
            added = "",
            modified = "";
    if(dbStatus && (id >=0) ) {
        request = QSqlQuery(db);
        request.exec("select ID, Title, Attributes, changedFiles, dateAdded, dateModified from contacts where ID=\'" + QString::number(id) + "\'");
        while(request.next()) {
            ID = request.value(0).toInt();
            title = request.value(1).toString();
            attr = request.value(2).toString();
            changed = request.value(3).toString();
            added = request.value(4).toString();
            modified = request.value(5).toString();
            result.append( {ID, title, attr, changed, added, modified} );
        }
        //qDebug() << "got: "<< title << " + " << attr;
        return result;
    } else {
        qDebug() << "Database doesn't open";
    }
}

int dbAccess::addNewContact(QString id, QString title, QString attr, QString changed) {
    if(dbStatus) {
        request = QSqlQuery(db);
        int idNum = 0;
        QString idStr = "";
        if( (idNum = id.toInt()) >= 0) {
            idStr = id;
        }
        idStr = "";//temp for debug
        //QString strVariables = "\"" + idStr + "\",\"" + title + "\",\"" + attr + "\",\"" + changed + "\",\"" + dateAdded + "\",\"" + dateModifoed + "\"";
        QString strVariables = "\"" + idStr + "\",\"" + title + "\",\"" + attr + "\",\"" + changed + "\",now(),now()";
        request.exec("insert into contacts (ID,Title, Attributes, changedFiles, dateAdded, dateModified) values(" + strVariables + ")");
        if(db.isOpenError()) {
            qDebug() << "error while insert" << db.lastError();
        }
        return 1;
    }
}

//shuffle QString argument, return 1, save to input argument strIN (pointer)
int dbAccess::gen_random_str(QString &strIN) {
    QChar tmp;
    int res_size = strIN.size();
    int rand_f = 0;
    int rand_g = 0;
    for(int i = 0; i < res_size; i++) {
        rand_f = qrand() % res_size;
        rand_g = qrand() % res_size;
        tmp = strIN[rand_f];
        strIN[rand_f] = strIN[rand_g];
        strIN[rand_g] = tmp;
    }
    return 1;
}
