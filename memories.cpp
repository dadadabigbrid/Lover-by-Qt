#include "memories.h"
#include "ui_memories.h"

#include<QPixmap>
#include<QSize>
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
#include<QDebug>

Memories::Memories(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Memories)
{
    ui->setupUi(this);
    init();

    labelPhoto = ui->label;
}

Memories::~Memories()
{
    delete ui;
}

void Memories::init()
{
    QSize size;
    size.setWidth(138);
    size.setHeight(138);

    QPixmap open(tr(":/new/p2/icon/open.png"));
    ui->btn_open->setIcon(open);
    ui->btn_open->setIconSize(size);

    QPixmap close(tr(":/new/p2/icon/close.png"));
    ui->btn_close->setIcon(close);
    ui->btn_close->setIconSize(size);

    /*QPixmap big(tr(":/new/p2/icon/big.png"));
    ui->btn_big->setIcon(big);
    ui->btn_big->setIconSize(size);

    QPixmap small(tr(":/new/p2/icon/small.png"));
    ui->btn_small->setIcon(small);
    ui->btn_small->setIconSize(size);*/

    QPixmap last(tr(":/new/p2/icon/last.png"));
    ui->btn_last->setIcon(last);
    ui->btn_last->setIconSize(size);

    QPixmap next(tr(":/new/p2/icon/next.png"));
    ui->btn_next->setIcon(next);
    ui->btn_next->setIconSize(size);
    //使窗口顶端显示
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
}

void Memories::openFile()
{
    /*filename=QFileDialog::getOpenFileName(this,
                                          tr("选择图像"),
                                          "E://MyWorkSpace//Qt//Lover//photo",
                                          tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));*/
    filename = ("E://MyWorkSpace//Qt//Lover//photo//6.png");
    if(filename.isEmpty())
    {
        qDebug() << "filename 为空";
        return;
    }
    else
    {
        qDebug() << filename;
        QImage* img=new QImage;

        if(! ( img->load(filename) ) ) //加载图像
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            delete img;
            return;
        }
        ui->label->setPixmap(QPixmap::fromImage(*img));
    }
}

int Memories::getFileCurIndex()
{
    QFileInfo info;
    int j;

    if (fileInfoList.count() <= 0)
    {
        qDebug() << "fileInfoList is NULL!";
        return -1;
    }

    for (j = 0; j < fileInfoList.count(); j++)
    {
        info = fileInfoList.at(j);
        if (info.fileName() == fileInfo.fileName())
        {
            break;
        }
    }

    /*if (j >= fileInfoList.count())
    {
        qDebug() << "Not find current file!";
        return -1;
    }*/

    index = j;
    qDebug() << "Current fileInfo index: " << index;

    return index;
}

int Memories::getfileInfoList()
{
    QFileInfo info;
    QFileInfoList infoList;

    path = QFileInfo(filename).absolutePath();
    dir = QFileInfo(filename).absoluteDir();

    fileInfoList.clear();

    infoList = dir.entryInfoList(QDir::Files);
    for (int i = 0; i < infoList.count(); i++)
    {
        info = infoList.at(i);
        QString suffix = info.suffix();

        if (suffix == "jpg" || suffix == "bmp" || suffix == "png"
            || suffix == "gif" || suffix == "jpeg")
        {
            fileInfoList.append(info);
        }
    }

    return 0;
}

int Memories::last()
{
    if (index < 0)
    {
        return -1;
    }

    while (1) {
        index = index - 1;
        int count = fileInfoList.count();
        if (index < 0)
        {
            QMessageBox::information(this, tr("Tip"), tr("This is the first image."));
            index = count - 1;
        }

        filename.clear();
        filename.append(path);
        filename += "/";
        filename += fileInfoList.at(index).fileName();

        if (!QFile(filename).exists())
        {
            fileInfoList.removeAt(index);
            continue;
        } else
        {
            break;
        }
    }

    angle = 0;
    size = QSize(0, 0);
    return 0;
}
int Memories::next()
{
    if (index < 0)
    {
        return -1;
    }

    while (1)
    {
        index = index + 1;
        int count = fileInfoList.count();
        if (index == count)
        {
            QMessageBox::information(this, tr("Tip"), tr("This is the last image."));
            index = 0;
        }

        filename.clear();
        filename.append(path);
        qDebug() << path;
        filename += "/";
        filename += fileInfoList.at(index).fileName();

        if (!QFile(filename).exists())
        {
            fileInfoList.removeAt(index);
            continue;
        } else
        {
            break;
        }
    }

    angle = 0;
    size = QSize(0, 0);
    return 0;
}

void Memories::on_btn_next_clicked()
{
    next();
    if(filename.isEmpty())
    {
        qDebug() << "filename 为空";
        return;
    }
    else
    {
        QImage* img=new QImage;

        if(! ( img->load(filename) ) ) //加载图像
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            delete img;
            return;
        }
        ui->label->setPixmap(QPixmap::fromImage(*img));
    }
}

void Memories::on_btn_last_clicked()
{
    last();
    if(filename.isEmpty())
    {
        qDebug() << "filename 为空";
        return;
    }
    else
    {
        QImage* img=new QImage;

        if(! ( img->load(filename) ) ) //加载图像
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            delete img;
            return;
        }
        ui->label->setPixmap(QPixmap::fromImage(*img));
    }
}

void Memories::on_btn_open_clicked()
{
    openFile();
    getfileInfoList();
    index = getFileCurIndex();
}

void Memories::on_btn_close_clicked()
{
    close();
}
