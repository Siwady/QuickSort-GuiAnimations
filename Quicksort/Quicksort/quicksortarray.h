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
    ~QuickSortArray();
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
    int End;
    int Begin;
    bool Swap;

    void QuickSort3Ways(int left, int right);
    void swap(int a, int b);

    bool Play;
    int currentStep;
    void NextStep();
    void PreviousStep();
    void PlayQuickSort();
    void GenerateSteps(int i);

    static void msleep(unsigned long msecs){QThread::msleep(msecs);}   //Sleeper::msleep(10);
    static void sleep(unsigned long secs){QThread::sleep(secs);}    //Sleeper::sleep(10);

private:
    QColor color;

};

class QuickSortStep
{
public:
    QuickSortStep(){}
    QuickSortStep(int begin,int end,int leftIndex,int rightIndex,int pivotIndex,bool swap,QList<int> items)
    {
        this->Begin=begin;
        this->End=end;
        this->LeftIndex=leftIndex;
        this->RightIndex=rightIndex;
        this->PivotIndex=pivotIndex;
        this->Items=items;
        this->Swap=swap;
    }
    int LeftIndex, RightIndex,PivotIndex,Begin,End,Swap;
    QList<int> Items;

};

#endif // QUICKSORTARRAY_H
