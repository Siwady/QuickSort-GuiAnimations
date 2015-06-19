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
    this->Swap=false;
}

QuickSortArray::~QuickSortArray()
{
    delete renderArea;
}

void QuickSortArray::Add(int number)
{
    this->items.push_back(number);
}

void QuickSortArray::RenderArray(QPainter *painter)
{
    painter->setBrush(this->color);
    painter->setPen(Qt::black);
    QPixmap arrow1,pivot;
    pivot.load("://Images/Pivot2.png");
    arrow1.load("://Images/Arrow.png");

    for(int i=0;i<this->items.size();i++)
    {
        if(i==Begin || i==End)
            painter->drawPixmap((880/2)-((items.size()*30)/2)+(i*30),100,30,30,arrow1);   // este es el del arrow.

        if(i==pivotIndex)
        {
            painter->drawPixmap((880/2)-((items.size()*30)/2)+(i*30),40,30,30,pivot);
            /*painter->setBrush(Qt::cyan);
            painter->drawRect((880/2)-((items.size()*30)/2)+(i*30),70,this->ItemSize,this->ItemSize); // de 30 en 30 el offset
            painter->drawText((880/2)-((items.size()*30)/2)+(i*30)+((ItemSize/2)-3),70+((ItemSize/2)+3), QString::number(this->items.at(i)));*/
        }
        if(i==indexA || i==indexB){
            if(this->Swap)
                painter->setBrush(Qt::cyan);
            else
                painter->setBrush(Qt::yellow);

            painter->drawRect((880/2)-((items.size()*30)/2)+(i*30),70,this->ItemSize,this->ItemSize); // de 30 en 30 el offset
            painter->drawText((880/2)-((items.size()*30)/2)+(i*30)+((ItemSize/2)-3),70+((ItemSize/2)+3), QString::number(this->items.at(i)));
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

    this->steps.push_back(new QuickSortStep(left,right,i,j,pivotIndex,false,this->items));
    while (i <= j) {
          while (items[i] < pivot){
              indexA=i;
              indexB=j;
              this->steps.push_back(new QuickSortStep(left,right,i,j,pivotIndex,false,this->items));
              i++;

          }
          while (items[j] > pivot){
              indexA=i;
              indexB=j;
              this->steps.push_back(new QuickSortStep(left,right,i,j,pivotIndex,false,this->items));
              j--;

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
                this->steps.push_back(new QuickSortStep(left,right,i,j,pivotIndex,true,this->items));
                i++;
                j--;
          }
    };
    if (left < j)
          QuickSort(left, j);

    if (i < right)
          QuickSort(i, right);
}

void QuickSortArray::QuickSort3Ways(int left, int right)
{
    if(right>left)
    {
        int l=left;
        int r=right;
        int i=left+1;
        this->indexA=i;
        this->indexB=r;
        this->pivotIndex=left;
        int pivot=this->items.at(this->pivotIndex);

        while(i<=r)
        {
            if(this->items.at(i)<pivot)
            {
                swap(i,l);
                if(i==pivotIndex)
                    pivotIndex=l;
                else if(l==pivotIndex)
                    pivotIndex=i;
                this->steps.push_back(new QuickSortStep(left,right,l,r,pivotIndex,true,this->items));
                i++;
                l++;
            }else if(pivot<this->items.at(i))
            {
                swap(i,r);
                if(i==pivotIndex)
                    pivotIndex=r;
                else if(r==pivotIndex)
                    pivotIndex=i;
                this->steps.push_back(new QuickSortStep(left,right,l,r,pivotIndex,true,this->items));
                r--;
            }else{
                this->steps.push_back(new QuickSortStep(left,right,l,r,pivotIndex,false,this->items));
                i++;
            }
        }

        QuickSort3Ways(left,l-1);
        QuickSort3Ways(r+1,right);
    }
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
        this->Swap=steps.at(currentStep)->Swap;
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
        this->Swap=steps.at(currentStep)->Swap;
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
        this->Swap=steps.at(currentStep)->Swap;
        this->items.clear();
        for(int i=0;i<steps.at(currentStep)->Items.size();i++)
            Add(steps.at(currentStep)->Items.at(i));

        this->renderArea->repaint();
        this->msleep(100);
        currentStep++;
    }
}

void QuickSortArray::GenerateSteps(int i)
{
    if(i==0)
        QuickSort(0,this->items.size()-1);
    else if(i==1)
        QuickSort3Ways(0,this->items.size()-1);
    //QuickSort(0,this->items.size()-1);
    this->steps.push_back(new QuickSortStep(-1,-1,-1,-1,-1,false,this->items));
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

