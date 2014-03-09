#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "dbaccess.h"
#include "netaccess.h"
#include <qsystemtrayicon.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    int getTitles();
    int getQuery();
    int addnew();
    void trayAct();
    void trayInit();
    void test_network();

private:
    Ui::MainWindow *ui;

private:
    dbAccess conn;
    //key TID;
    QList<key> Storage;
    QSystemTrayIcon *tray;
    QIcon icon;
    bool trayState;
};

#endif // MAINWINDOW_H
