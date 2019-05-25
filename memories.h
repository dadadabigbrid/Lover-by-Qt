#ifndef MEMORIES_H
#define MEMORIES_H

#include <QWidget>
#include<QLabel>
#include<QFileInfo>
#include<QDir>

namespace Ui {
class Memories;
}

class Memories : public QWidget
{
    Q_OBJECT

public:
    explicit Memories(QWidget *parent = nullptr);
    ~Memories();

    int index;
    int angle;
    QLabel *labelPhoto;
    QString filename;
    QFileInfo fileInfo;
    QFileInfoList fileInfoList;
    QString path;
    QDir dir;
    QSize size;


    void init();
    void openFile();
    int getFileCurIndex();
    int getfileInfoList();
    int last();
    int next();

private slots:
    void on_btn_open_clicked();

    void on_btn_close_clicked();

    void on_btn_next_clicked();

    void on_btn_last_clicked();

private:
    Ui::Memories *ui;
};

#endif // MEMORIES_H
