#include "renderarea.h"

RenderArea::RenderArea(QuickSortArray *Q, QWidget *parent) :
    QWidget(parent)
{
     this->QArray=Q;// <----
}

void RenderArea::setArray(QuickSortArray *qArray)
{
    this->QArray = qArray;
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawRect(0,0,this->width()-1,this->height()-1);
    this->QArray->RenderArray(&painter);
}


