#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>

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
    int simpleRead();
    void log();

private:
    Ui::MainWindow *ui;

private:
    QString hostname;
    QString dbAlias;
    QString login;
    QString password;
    qint16 port;
    //QVector<int> list;

    //@i = number in QListTable
    //@id = ID in table contacts
    //@title = Title in table contacts
    struct pair {
        qint16 i;
        qint16 id;
        QString title;
    };
    QVector< pair > vect;
};

#endif // MAINWINDOW_H
