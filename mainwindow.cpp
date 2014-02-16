#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(getTitles()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(addnew()));
    connect(ui->listWidget,SIGNAL(itemSelectionChanged()),this,SLOT(getQuery()));

    conn.initialize("localhost",3306,"qtTest","root","tbls8541");
    conn.dbOpen();
}

MainWindow::~MainWindow()
{
    conn.dbClose();
    delete ui;
}

int MainWindow::getTitles() {
    ui->listWidget->clear();
    Storage.clear();//fucking memory eater
    QList<key> response = conn.getTitleID();
    int i = response.size();
    for(int ii = 0; ii < i; ii++) {
        ui->listWidget->addItem(response.value(ii).Title);
        Storage.append({response.value(ii).ID, response.value(ii).Title});
    }
    ui->label->setText("total: " + QString::number(i) + " items");
    ui->statusBar->showMessage("List refreshed.",5000);
    return 1;
}

int MainWindow::getQuery() {
    QList<base> result;
    int id = 0, listID = 0;//this is id of list, not ID in table
    listID = ui->listWidget->currentRow();
    id = Storage.value(listID).ID;
    result = conn.getBodyByID(id);
    ui->lineEdit->setText(result.value(0).Title);
    ui->textEdit->setText(result.value(0).Additional);
    ui->textEdit_2->setText(result.value(0).ChangedFiles);
    return 1;
}

int MainWindow::addnew() {
    QString title = "1234567890",
            descr = "doigj dxlfkbvjdfigjd xlksdfg bfxghdfhfcg",
            changed = "fghfh ngyjf ghncfhd xrfgd xfdrtg dgfcg cfgd gdg cbgdgdf";
    for(int c = 0; c < 20000; c++) {
        QCoreApplication::processEvents();
        if(!ui->checkBox->isChecked()) {
            qDebug() << "stoped or not enabled";
            return 0;
        }
        conn.gen_random_str(title);
        conn.gen_random_str(descr);
        conn.gen_random_str(changed);
        conn.addNewContact("0", title, descr, changed);
        //qDebug() << "iteration: " << c;
        ui->statusBar->showMessage(QString::number(c),5000);
    }
    return 1;
}
