#include "whisper.h"
#include "ui_whisper.h"

#include<QFile>
#include<QTextStream>
#include<QDateTime>

Whisper::Whisper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Whisper)
{
    ui->setupUi(this);
    init();
}

Whisper::~Whisper()
{
    delete ui;
}

void Whisper::init()
{
    //使窗口顶端显示
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
    QFile file("E://MyWorkSpace//Qt//Lover//whisper.data");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream out(&file);
    int count = 1;
    list.clear();
    while(!out.atEnd())
    {
        word temp;
        temp.str = out.readLine();
        temp.row = count++;
        list.append(temp);
    }
    showWhisper();
}

void Whisper::add()
{
    word temp;
    temp.str = ui->lineEdit->text();
    temp.row = ui->listWidget->count() + 1;
    list.append(temp);
    save(temp);
    showWhisper();
}

void Whisper::save(word w)
{
    QFile file("E://MyWorkSpace//Qt//Lover//whisper.data");
    file.open(QIODevice::Append|QIODevice::Text);
    QTextStream out(&file);
    QDateTime time = QDateTime::currentDateTime();
    QString date_str = time.toString();
    out << w.str;
    out << "#";
    out << date_str;
    out << endl;
}

void Whisper::showWhisper()
{
    ui->listWidget->clear();
    int count = 0;
    for(int i = 0;i < list.count();i++)
    {
        ui->listWidget->addItem(list[i].str);
        list[i].row = count;
        count++;
    }
}

void Whisper::on_btn_add_clicked()
{
    add();
    ui->lineEdit->clear();
}

void Whisper::on_btn_close_clicked()
{
    close();
}

