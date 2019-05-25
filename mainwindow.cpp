#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "punrecord.h"
#include "memories.h"
#include "confirm.h"

#include <QtCore>
#include <QFile>
#include <QTextCodec>
#include <QMessageBox>
#include <QDateTime>
#include <QList>
#include <QDebug>
#include<QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initToDoList();
    setWindowFlag(Qt::WindowStaysOnTopHint);

    frequency = getfrequency();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addList()
{
    memoitem item;
    item.done=0;

    item.contanct = ui->lineEdit->text();

    QDateTime time = QDateTime::currentDateTime();
    QString str = "#";
    str += time.toString("yyyy-MM-dd hh:mm:ss ddd");
    item.begintime = str;
    item.row = -1;

    memoItem.append(item);

    ui->lineEdit->clear();

    showTodo();
}

void MainWindow::deleteList()
{
    if (ui->listWidget->currentItem()==nullptr)
    {
        ui->doneButton->setEnabled(false);
        return ;
    }

    QString contant = ui->listWidget->currentItem()->text();
    qDebug()<<"crnt row:"<<ui->listWidget->currentRow()<<endl;

    int index = findMemoItemIndex(contant,ui->listWidget->currentRow());
    memoItem[index].done=1;
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    memoItem[index].endtime = str;

    //listWidget->takeItem(listWidget->currentRow());
    showTodo();
    showDone();

}

/*void MainWindow::addButtonEnableFunc()
{
    ui->addButton->setEnabled(!(ui->lineEdit->text().isEmpty()));
}

void MainWindow::doneButtonEnableFunc()
{
    ui->doneButton->setEnabled(ui->listWidget->currentItem()!=nullptr);
}*/

void MainWindow::cleanCookie()
{
    QList<memoitem>::iterator i;
    i=memoItem.begin();
    for (i=memoItem.begin(); i!=memoItem.end(); i++)
    {
        if((*i).done==1)
        {
            i=memoItem.erase(i);
            i--;
        }
    }
    //qDebug()<<memoItem.count();
    ui->doneList->clear();
}

void MainWindow::initToDoList()
{

    QFile file("E://MyWorkSpace//Qt//Lover//list.data");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        return;
    }

    QTextStream in(&file);
    while( !in.atEnd())
    {
        memoitem item;

        QString line = in.readLine();
        (line=="0")? (item.done=0) : (item.done=1);

        line = in.readLine();
        item.contanct = line;
        line = in.readLine();
        item.begintime = line;

        if (item.done==1)
        {
            line = in.readLine();
            item.endtime = line;
        }

        memoItem.append(item);
    }
    in.flush();
    file.close();

    showTodo();
    showDone();
}

void MainWindow::saveBeforeExit()
{

    QFile file("E://MyWorkSpace//Qt//Lover//List.data");
    file.remove();
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream out(&file);
    for (int i=0; i<memoItem.count(); i++)
    {
        out<<memoItem[i].done<<endl;
        out<<memoItem[i].contanct<<endl;
        out<<memoItem[i].begintime<<endl;
        if(memoItem[i].done==1)
            out<<memoItem[i].endtime<<endl;
    }
    out.flush();
    file.close();
}

void MainWindow::dateShow()
{
    if (!ui->listWidget->currentItem())
    {
        ui->dateLabel->setText("");
        return ;
    }
    int index = findMemoItemIndex(ui->listWidget->currentItem()->text(),ui->listWidget->currentRow());
    if (index>=0)
        ui->dateLabel->setText(memoItem[index].begintime);
}

/*void MainWindow::close_Event( QCloseEvent * event )
{
    saveBeforeExit();
    event->accept();
}*/

inline int MainWindow::findMemoItemIndex(QString s,int row)
{
    for(int i=0; i<memoItem.count(); i++)
    {
        qDebug()<<memoItem[i].contanct<<"  "<<memoItem[i].row<<endl;
        if (memoItem[i].contanct == s && memoItem[i].row == row)
            return i;
    }
    return -1;
}

void MainWindow::showDone()
{
    ui->doneList->clear();
    for(int i=0; i<memoItem.count(); i++)
    {
        if (memoItem[i].done==1)
        {
            QString temp = memoItem[i].contanct;
            temp += "   ";
            temp += memoItem[i].begintime;
            temp += "--";
            temp += memoItem[i].endtime;
            ui->doneList->addItem(temp);
        }
    }
}

void MainWindow::showTodo()
{
    ui->listWidget->clear();
    int count = 0;
    for(int i=0; i<memoItem.count(); i++)
    {
        if (memoItem[i].done==0)
        {
            ui->listWidget->addItem(memoItem[i].contanct);
            memoItem[i].row = count;
            count++;
        }
    }
}

int MainWindow::getfrequency()
{
    int frequency = 0;
    QFile file("E://MyWorkSpace//Qt//Lover//recoder.data"
               "");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","无法打开文件","确定");
        return -1;
    }
    QTextStream out(&file);
    while(!out.atEnd())
    {
        QString line = out.readLine();
        frequency ++;
    }
    return frequency;
}

void MainWindow::on_addButton_clicked()
{
    if(ui->lineEdit->text().length() == 0)
        return;
    addList();
    dateShow();
}

void MainWindow::punch()
{
    QFile file("E://MyWorkSpace//Qt//Lover//recoder.data");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream out(&file);

    QDateTime time = QDateTime::currentDateTime();
    QString str = "#";
    str += time.toString("yyyy-MM-dd hh:mm:ss ddd");
    frequency++;

    //int frequency = MainWindow::frequency;
    out << frequency << str << endl;

    str = "次" + str;
    QString str2;
    str2 = QString::number(frequency);
    str = str2 + str;
    str = "已打卡" + str;
    qDebug() << str;
    ui->labelWord->setText(str);
    //QMovie *movie = new QMovie(":/new/p/image/timg.gif");
    //ui->labelPhoto->setMovie(movie);
    ui->labelPhoto->setPixmap(QPixmap(":/new/p/image/timg.gif"));

    out.flush();
    file.close();
}

void MainWindow::on_doneButton_clicked()
{
    deleteList();
}

void MainWindow::on_clean_clicked()
{
    cleanCookie();
}

void MainWindow::on_btn_punrecord_clicked()
{
    punRecord *pun = new punRecord;
    pun->show();
}

void MainWindow::on_btn_punch_clicked()
{
    punch();
    ui->btn_punch->setText("打卡成功!");
    dateShow();
}

void MainWindow::on_pushButton_2_clicked()
{
    Memories *m = new Memories;
    m->show();
}

void MainWindow::on_pushButton_clicked()
{
    confirm *c = new confirm;
    c->show();
}
