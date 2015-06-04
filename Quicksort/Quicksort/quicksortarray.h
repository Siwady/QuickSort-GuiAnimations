#ifndef QUICKSORTARRAY_H
#define QUICKSORTARRAY_H

#include <QPainter>


class QuickSortArray
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
private:
    QColor color;

};

#endif // QUICKSORTARRAY_H
