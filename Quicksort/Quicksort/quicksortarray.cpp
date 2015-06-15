#include "quicksortarray.h"
#include "renderarea.h"
#include <QPicture>
#include <QMessageBox>
#include <QDebug>

QuickSortArray::QuickSortArray()
{
    this->color = Qt::white;
    this->ItemSize=30;
    this->renderArea = new RenderArea(this);
    this->indexA=-1;
    this->indexB=-1;
    this->pivotIndex=-1;
    this->currentStep=0;
    this->Play=false;
}

void QuickSortArray::Add(int number)
{
    this->items.push_back(number);
}

void QuickSortArray::RenderArray(QPainter *painter)
{
    painter->setBrush(this->color);
    painter->setPen(Qt::black);
    QPixmap arrow1;
    arrow1.load("://Images/Arrow.png");

    for(int i=0;i<this->items.size();i++)
    {
        if(i==Begin || i==End)
            painter->drawPixmap((880/2)-((items.size()*30)/2)+(i*30),100,30,30,arrow1);   // este es el del arrow.

        if(i==pivotIndex)
        {
            painter->setBrush(Qt::cyan);
            painter->drawRect((880/2)-((items.size()*30)/2)+(i*30),70,this->ItemSize,this->ItemSize); // de 30 en 30 el offset
            painter->drawText((880/2)-((items.size()*30)/2)+(i*30)+((ItemSize/2)-3),70+((ItemSize/2)+3), QString::number(this->items.at(i)));
        }else if(i==indexA || i==indexB){

            painter->setBrush(Qt::yellow);

            painter->drawRect((880/2)-((items.size()*30)/2)+(i*30),70,this->ItemSize,this->ItemSize); // de 30 en 30 el offset
            painter->drawText((880/2)-((items.size()*30)/2)+(i*30)+((ItemSize/2)-3),30+((ItemSize/2)+3), QString::number(this->items.at(i)));
        }else{
            painter->setBrush(this->color);
            painter->drawRect((880/2)-((items.size()*30)/2)+(i*30),70,this->ItemSize,this->ItemSize); // de 30 en 30 el offset
            painter->drawText((880/2)-((items.size()*30)/2)+(i*30)+((ItemSize/2)-3),70+((ItemSize/2)+3), QString::number(this->items.at(i)));
        }
    }
}

int QuickSortArray::Get(int index)
{
    return this->items.at(index);
}

int QuickSortArray::GetSize()
{
    return this->items.size();
}


void QuickSortArray::QuickSort(int left, int right) {
    int i = left, j = right;
    int temp;
    int pivot = items[(left + right) / 2];
    this->pivotIndex=(left + right) / 2;

    this->steps.push_back(new QuickSortStep(left,right,i,j,pivotIndex,this->items));
    while (i <= j) {
          while (items[i] < pivot){
              indexA=i;
              indexB=j;
              this->steps.push_back(new QuickSortStep(left,right,i,j,pivotIndex,this->items));
              i++;
              //msleep(500);
              //this->renderArea->repaint();

          }
          while (items[j] > pivot){
              indexA=i;
              indexB=j;
              this->steps.push_back(new QuickSortStep(left,right,i,j,pivotIndex,this->items));
              j--;
              //msleep(500);

             // this->renderArea->repaint();

          }if (i <= j) {
                if(i==pivotIndex)
                    pivotIndex=j;
                else if(j==pivotIndex)
                    pivotIndex=i;
                indexA=i;
                indexB=j;
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
                this->steps.push_back(new QuickSortStep(left,right,i,j,pivotIndex,this->items));
                i++;
                j--;
                //msleep(1000);

               // this->renderArea->repaint();
          }

    };

    //this->renderArea->repaint();

    if (left < j)
          QuickSort(left, j);
   // this->renderArea->repaint();

    if (i < right)
          QuickSort(i, right);

    //this->renderArea->repaint();

    //indexA=indexB=pivotIndex=this->items.size()+1;

}

void QuickSortArray::QuickSort3Ways(int left, int right)
{

}

void QuickSortArray::swap(int a, int b)
{
    int temp;
    temp = items[a];
    items[a] = items[b];
    items[b] = temp;
}

void QuickSortArray::NextStep()
{
    if(currentStep+1<steps.size())
    {
        currentStep++;
        this->End=steps.at(currentStep)->End;
        this->Begin=steps.at(currentStep)->Begin;
        this->indexA=steps.at(currentStep)->LeftIndex;
        this->indexB=steps.at(currentStep)->RightIndex;
        this->pivotIndex=steps.at(currentStep)->PivotIndex;
        this->items.clear();
        for(int i=0;i<steps.at(currentStep)->Items.size();i++)
            Add(steps.at(currentStep)->Items.at(i));

        this->renderArea->repaint();
        //this->msleep(100);
    }
}

void QuickSortArray::PreviousStep()
{
    if(currentStep>0)
    {
        currentStep--;
        this->End=steps.at(currentStep)->End;
        this->Begin=steps.at(currentStep)->Begin;
        this->indexA=steps.at(currentStep)->LeftIndex;
        this->indexB=steps.at(currentStep)->RightIndex;
        this->pivotIndex=steps.at(currentStep)->PivotIndex;
        this->items.clear();
        for(int i=0;i<steps.at(currentStep)->Items.size();i++)
            Add(steps.at(currentStep)->Items.at(i));

        this->renderArea->repaint();
        //this->msleep(100);

    }
}

void QuickSortArray::PlayQuickSort()
{
    currentStep++;
    while(currentStep<steps.size())
    {
        this->End=steps.at(currentStep)->End;
        this->Begin=steps.at(currentStep)->Begin;
        this->indexA=steps.at(currentStep)->LeftIndex;
        this->indexB=steps.at(currentStep)->RightIndex;
        this->pivotIndex=steps.at(currentStep)->PivotIndex;
        this->items.clear();
        for(int i=0;i<steps.at(currentStep)->Items.size();i++)
            Add(steps.at(currentStep)->Items.at(i));

        this->renderArea->repaint();
        this->msleep(100);
        currentStep++;
    }
}

void QuickSortArray::GenerateSteps()
{
    QuickSort(0,this->items.size()-1);
    this->steps.push_back(new QuickSortStep(-1,-1,-1,-1,-1,this->items));
    this->End=steps.at(currentStep)->End;
    this->Begin=steps.at(currentStep)->Begin;
    this->indexA=steps.at(currentStep)->LeftIndex;
    this->indexB=steps.at(currentStep)->RightIndex;
    this->pivotIndex=steps.at(currentStep)->PivotIndex;
    this->items.clear();
    for(int i=0;i<steps.at(currentStep)->Items.size();i++)
        Add(steps.at(currentStep)->Items.at(i));

    this->renderArea->repaint();

}

