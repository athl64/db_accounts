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

//now doesn't using
void MainWindow::log() {
    int index = 0;
    //return text of selected item in list
    ui->listWidget->selectedItems()[0]->text();
    //return index of selected item in list
    index = ui->listWidget->currentRow();
}

int MainWindow::getTitles() {
    ui->listWidget->clear();
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
    QString title = gen();
    conn.addNewContact("0", title, "good title", "some changed text");
    for(int c = 0; c < 20000; c++) {
        QCoreApplication::processEvents();
        if(!ui->checkBox->isChecked()) {
            qDebug() << "stoped or not enabled";
            return 0;
        }
        title = gen();
        conn.addNewContact("0", title, "good title", "some changed text");
        //qDebug() << "iteration: " << c;
        ui->statusBar->showMessage(QString::number(c),5000);
    }
    return 1;
}

//for debug
QString MainWindow::gen() {
    QString result;
    QList<QChar> tmp;
    tmp.append('a');
    tmp.append('b');
    tmp.append('c');
    tmp.append('d');
    tmp.append('e');
    tmp.append('f');
    //tmp[] filled

    qint8 i = 0;
    qint8 size = tmp.size();
    for(i = 0; i < size; i++) {
        result.append(tmp[i]);
    }
    //result filled from tmp[]

    quint8 random_f = 0, random_b;
    QChar tmp_char = '0';
    for(int i = 0; i <= size; i++) {
        random_f = qrand() % 6;
        random_b = qrand() % 6;
        tmp_char = tmp[random_f];
        tmp[random_f] = tmp[random_b];
        tmp[random_b] = tmp_char;
    }
    result.clear();//clear from first fill
    for(int i = 0; i < size; i++) {
        result.append(tmp[i]);
    }
    //result filled with shuffled tmp[]

    return result;
}
