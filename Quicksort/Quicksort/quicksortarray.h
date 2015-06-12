#ifndef QUICKSORTARRAY_H
#define QUICKSORTARRAY_H

#include <QPainter>
#include <QThread>
#include "renderarea.h"
class RenderArea;
class QuickSortStep;

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
    QList<QuickSortStep*> steps;
    int index;
    RenderArea *renderArea;
    int indexA;
    int indexB;
    int pivotIndex;

    bool Play;
    int currentStep;
    void NextStep();
    void PreviousStep();
    void PlayQuickSort();
    void GenerateSteps();

    static void msleep(unsigned long msecs){QThread::msleep(msecs);}   //Sleeper::msleep(10);
    static void sleep(unsigned long secs){QThread::sleep(secs);}    //Sleeper::sleep(10);

private:
    QColor color;

};

class QuickSortStep
{
public:
    QuickSortStep(){}
    QuickSortStep(int leftIndex,int rightIndex,int pivotIndex,QList<int> items)
    {
        this->LeftIndex=leftIndex;
        this->RightIndex=rightIndex;
        this->PivotIndex=pivotIndex;
        this->Items=items;
    }
    int LeftIndex, RightIndex,PivotIndex;
    QList<int> Items;

};

#endif // QUICKSORTARRAY_H
