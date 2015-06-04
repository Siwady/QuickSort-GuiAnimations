#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>

#include "quicksortarray.h"


class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);

    void setArray (QuickSortArray *qArray)
    {
        this->QArray = qArray;
    }


protected:
     void paintEvent(QPaintEvent *event);

    
signals:
    
public slots:
private:
    QuickSortArray *QArray;

};

#endif // RENDERAREA_H
