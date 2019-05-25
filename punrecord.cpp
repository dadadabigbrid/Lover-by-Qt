#include "punrecord.h"
#include "ui_punrecord.h"

#include<QFile>
#include<QMessageBox>
#include<QTextStream>
#include<QDateTime>
#include<QDateTime>

punRecord::punRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::punRecord)
{
    ui->setupUi(this);
    //frequency = getfrequency();
    recordshow();
    //使窗口顶端显示
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);

    //时间显示为当前时间
    QDateTime time = QDateTime::currentDateTime();
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);
}

punRecord::~punRecord()
{
    delete ui;
}

int punRecord::getfrequency()
{
    int frequency = 0;
    QFile file("E://MyWorkSpace//Qt//Lover//recoder.data");
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

void punRecord::recordshow()
{
    QFile file("E://MyWorkSpace//Qt//Lover//recoder.data");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","无法打开文件","确定");
        return;
    }
    QTextStream out(&file);
    QList<QString> list;
    /*while(!out.atEnd())
    {
        QString str = out.readLine();
        list.append(str);
        ui->listWidget->addItem(str);
    }*/
    QString str = out.readAll();
    ui->listWidget->addItem(str);
    file.close();
    out.flush();
}




void punRecord::on_pushButton_2_clicked()
{
    close();
}
