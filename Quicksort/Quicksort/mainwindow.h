#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <time.h>
#include <QLineEdit>
#include "quicksortarray.h"
#include <QTextEdit>

class QuickSortArray;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QStringList fields;
    void Fill();
    QuickSortArray *QuickSort;
    QList<QLineEdit*> EditList;
    bool play;
    QTimer *timer;

private slots:
    void on_OpenFile_triggered();
    void on_bt_play_clicked();

    void on_pb_generate_clicked();

    void on_pb_nextStep_clicked();

    void on_pb_previousStep_clicked();

    void on_pb_update_clicked();

    void Play();

    void on_SaveFile_triggered();

    void on_pb_Add_clicked();

    void on_pb_Delete_clicked();

private:
    Ui::MainWindow *ui;


    //QTime *timer;
};

#endif // MAINWINDOW_H
