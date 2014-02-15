#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "dbaccess.h"

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
    void log();
    int getTitles();
    int getQuery();
    int addnew();
    QString gen();

private:
    Ui::MainWindow *ui;

private:
    dbAccess conn;
    key TID;
    QList<key> Storage;
};

#endif // MAINWINDOW_H
