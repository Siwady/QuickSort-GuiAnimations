#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
    // this->QArray=new QuickSortArray();    // <----
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
   // this->QArray->RenderArray(&painter);
}


