#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(simpleRead()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(cl()));
    connect( ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(log()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::simpleRead() {
    //-----------------------
    hostname = "localhost";
    port = 3306;
    login = "root";
    password = "tbls8541";
    dbAlias = "qtTest";
    //-----------------------
    int i = 0;
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QODBC");
    myDB.setHostName(hostname);
    myDB.setPort(port);
    //DatabaseName for ODBC = name of DSN for DB in confugure window in control panel
    myDB.setDatabaseName(dbAlias);
    myDB.setUserName(login);
    myDB.setPassword(password);

    bool status = myDB.open();
    //qDebug() << myDB.lastError();

    //clear list before new request
    this->ui->listWidget->clear();

    //request for contact titles
    QSqlQuery *query = new QSqlQuery(myDB);
    query->exec("select ID, Title from contacts");
    while(query->next()) {
        this->ui->listWidget->insertItem(i,query->value(1).toString());
        //list.append(query->value(0).toInt());
        vect.append({i,query->value(0).toInt(),query->value(1).toString()});
        i++;
    }

    myDB.close();
    return 1;
}

void MainWindow::log() {
    int index = 0;
    //return text of selected item in list
    ui->listWidget->selectedItems()[0]->text();
    //return index of selected item in list
    index = ui->listWidget->currentRow();
}

int MainWindow::cl() {
    dbAccess conn;
    conn.initialize("localhost",3306,"qtTest","root","tbls8541");
    conn.dbOpen();
    QList<QString> response = conn.getTitle();
    int i = response.size();
    for(int ii = 0; ii < i; ii++) {
        ui->textEdit->append(response[ii]);
    }
    QList<base> body = conn.getBody();
    conn.dbClose();
    return 1;
}
