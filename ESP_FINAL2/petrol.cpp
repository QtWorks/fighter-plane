#include "petrol.h"
#include <QGraphicsScene>
#include <QTimer>
#include <stdlib.h>
#include <QGraphicsPixmapItem>

Petrol::Petrol() : QObject(), QGraphicsPixmapItem()
{
    pos_x = 815;
    pos_y = rand() % 600;
    length = 30;
    height = 30;

    if(pos_y > 550)
    {
        pos_y -= 100;
    }

    else if(pos_y < 20)
    {
        pos_y += 100;
    }

    setPixmap(QPixmap(":/images/petrol_bubble.png"));
    setPos(pos_x,pos_y);

    QTimer *timer = new QTimer(this);
    connect (timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(10);
}

void Petrol::move()
{
    setPos(x()-2,y());

    if(pos().x() <= -pos_x - length)
    {
        scene()->removeItem(this);
        delete this;
    }
}
