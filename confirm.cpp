#include "confirm.h"
#include "ui_confirm.h"

#include <QtGlobal>
#include<QTime>
#include<QDebug>
#include<QMessageBox>

confirm::confirm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::confirm)
{
    ui->setupUi(this);
    index = init();
    //使窗口顶端显示
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
}

confirm::~confirm()
{
    delete ui;
}

int confirm::init()
{
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    index = qrand() % 3;
    showQuestion(index);
    return index;
}

void confirm::showQuestion(int index)
{
    w = new Whisper;

    switch (index)
    {
    case 0:
        ui->label->setText("0.你的第一次女装是什么时候:(月/日)");
        break;
    case 1:
        ui->label->setText("1.在一起纪念日是:(月/日)");
        break;
    case 2:
        ui->label->setText("2.女朋友的生日是:(月/日)");
        break;
    }
}

void confirm::on_btn_confirm_clicked()
{
    QString str = ui->lineEdit->text();
    bool flag = false;
    if(index == 0)
    {
        if(str == "00/00")
        {
            w->show();
            flag = true;
        }
        close();
    }
    if(index ==1)
    {
        if(str == "01/01")
        {
            w->show();
            flag = true;
        }
        close();
    }if(index == 2)
    {
        if(str == "02/02")
        {
            w->show();
            flag = true;
        }
            close();
    }
    if(flag == false)
        QMessageBox::critical(this,"error!","答案错误");
    ui->lineEdit->clear();
}

void confirm::on_btn_close_clicked()
{
    close();
}
