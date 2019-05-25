#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class memoitem{
public:
    int done;
    QString contanct;
    QString begintime;
    QString endtime;
    int row;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString timeRecord;
    QList<memoitem> memoItem;
    void initToDoList();
    void close_Event( QCloseEvent * event );
    int findMemoItemIndex(QString s, int row);
    void showDone();
    void showTodo();
    int frequency = 0;

    /*打卡区*/
    void punch();
    int getfrequency();

private slots:
    void on_addButton_clicked();

    void on_doneButton_clicked();

    void on_clean_clicked();

    void on_btn_punrecord_clicked();

    void on_btn_punch_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    void addList();
    void deleteList();
    void addButtonEnableFunc();
    void doneButtonEnableFunc();
    void saveBeforeExit();
    void dateShow();
    void cleanCookie();
};

#endif // MAINWINDOW_H
