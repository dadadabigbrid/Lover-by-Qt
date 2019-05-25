#ifndef CONFIRM_H
#define CONFIRM_H

#include <QWidget>
#include"whisper.h"

namespace Ui {
class confirm;
}

class confirm : public QWidget
{
    Q_OBJECT

public:
    explicit confirm(QWidget *parent = nullptr);
    ~confirm();

    int index;
    Whisper *w;

    int init();
    void showQuestion(int index);
private slots:
    void on_btn_confirm_clicked();

    void on_btn_close_clicked();

private:
    Ui::confirm *ui;
};

#endif // CONFIRM_H
