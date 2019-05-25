#ifndef WHISPER_H
#define WHISPER_H

#include <QWidget>

namespace Ui {
class Whisper;
}

typedef struct
{
    QString str;
    int row;
}word;
class Whisper : public QWidget
{
    Q_OBJECT

public:
    explicit Whisper(QWidget *parent = nullptr);
    ~Whisper();

    void init();
    void add();
    void save(word w);
    void showWhisper();

    QList<word> list;

private slots:
    void on_btn_add_clicked();

    void on_btn_close_clicked();

private:
    Ui::Whisper *ui;
};

#endif // WHISPER_H
