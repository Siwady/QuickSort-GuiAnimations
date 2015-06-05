#include "quicksortarray.h"
#include "renderarea.h"

QuickSortArray::QuickSortArray()
{
    this->color = Qt::white;
    this->ItemSize=30;
    this->renderArea = new RenderArea();
}

void QuickSortArray::Add(int number)
{
    this->items.push_back(number);
}

void QuickSortArray::RenderArray(QPainter *painter)
{
    painter->setBrush(this->color);
    painter->setPen(Qt::black);

    for(int i=0;i<this->items.size();i++)
    {
        if(i==4 || i==10)
            painter->setBrush(Qt::yellow);
        else
            painter->setBrush(this->color);
        painter->drawRect((880/2)-((items.size()*30)/2)+(i*30),50,this->ItemSize,this->ItemSize); // de 30 en 30 el offset
        painter->drawText((880/2)-((items.size()*30)/2)+(i*30)+((ItemSize/2)-3),50+((ItemSize/2)+3), QString::number(this->items.at(i)));
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

    /* partition */
    while (i <= j) {
          while (items[i] < pivot)
                i++;
          while (items[j] > pivot)
                j--;
          if (i <= j) {
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
                i++;
                j--;
          }
    };
    /* recursion */

    if (left < j)
          QuickSort(left, j);


    if (i < right)
          QuickSort(i, right);


}
