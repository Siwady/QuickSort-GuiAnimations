#ifndef QUICKSORTARRAY_H
#define QUICKSORTARRAY_H

#include <QPainter>
#include <QThread>
#include "renderarea.h"

class RenderArea;

class QuickSortArray: public QThread
{
public:
    QuickSortArray();
    void Add(int number);
    void RenderArray(QPainter *painter);
    int Get(int index);
    int GetSize();
    void setColor(QColor C) { this->color = C;}
    QColor getColor() const { return this->color; }
    int ItemSize;
    void QuickSort(int left, int right);
    QList<int> items;
    int index;
    RenderArea *renderArea;
    int indexA;
    int indexB;
    int pivotIndex;


    static void msleep(unsigned long msecs){QThread::msleep(msecs);}   //Sleeper::msleep(10);
    static void sleep(unsigned long secs){QThread::sleep(secs);}    //Sleeper::sleep(10);

private:
    QColor color;

};

#endif // QUICKSORTARRAY_H
