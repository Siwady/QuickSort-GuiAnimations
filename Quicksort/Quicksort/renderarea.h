#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>

#include "quicksortarray.h"

class QuickSortArray;

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QuickSortArray *Q,QWidget *parent = 0);

    void setArray (QuickSortArray *qArray);

    QuickSortArray *QArray;


protected:
     void paintEvent(QPaintEvent *event);
     void enterEvent ( QEvent * event ) ;
    
signals:
    
public slots:
private:

};

#endif // RENDERAREA_H
