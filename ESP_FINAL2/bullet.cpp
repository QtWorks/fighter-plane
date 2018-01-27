#include "bullet.h"
#include <QTimer>
#include <QList>
#include <pillar.h>
#include <QGraphicsScene>

Bullet::Bullet():QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/images/bullet.png"));
    QTimer *timer = new QTimer(this);
    connect (timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(25);
}

void Bullet::move()
{

    //move bullet up
        setPos(x()+10,y());

    //destroy bullet as it touches boundary of screen
        if(pos().x() > 800)
        {
            scene()->removeItem(this);
            delete this;
        }
}
