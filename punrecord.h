#ifndef PUNRECORD_H
#define PUNRECORD_H

#include <QWidget>

namespace Ui {
class punRecord;
}

class punRecord : public QWidget
{
    Q_OBJECT

public:
    explicit punRecord(QWidget *parent = nullptr);
    ~punRecord();

    int frequency = 0;

    int getfrequency();
    void recordshow();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::punRecord *ui;
};

#endif // PUNRECORD_H
