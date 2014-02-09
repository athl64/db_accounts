#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(simpleRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::simpleRead() {
    //declare objects
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QODBC");
    //initialize
    myDB.setHostName("localhost");
    myDB.setPort(3306);
    myDB.setDatabaseName("qtTest");
    myDB.setUserName("root");
    myDB.setPassword("password");
    //open
    bool status = myDB.open();
    //qDebug() << myDB.lastError();
    QSqlQuery *query = new QSqlQuery(myDB);
    query->exec("select name, descr from testing");
    while(query->next()) {
        this->ui->textEdit->append(query->value(0).toString() + ' \n ' + query->value(1).toString());
    }
    //close
    myDB.close();
    return 1;
}
