#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QTimer>
#include <time.h>
#include <QLineEdit>
#include "quicksortarray.h"

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
private slots:
    void on_OpenFile_triggered();
    void on_bt_play_clicked();

private:
    Ui::MainWindow *ui;
    QuickSortArray *QuickSort;

    QTime *timer;
};

#endif // MAINWINDOW_H
