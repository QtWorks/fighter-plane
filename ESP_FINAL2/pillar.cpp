//header file helps to draw Rect OBJECT
#include "pillar.h"
#include <time.h>
#include <stdlib.h>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "bullet.h"
#include "plane.h"
#include <QMediaPlayer>

Pillar::Pillar()
    //Calling Base Class Default Constructors
    : QObject(),QGraphicsPixmapItem()
{
    hp = 100;

    // srand(time(NULL));
    int randomNum = rand() %  450;

    pos_x = 0;
    pos_y = 0;
    length = 25;
    height = 115;

    setPixmap(QPixmap(":/images/pillar.png"));
    setPos(800,randomNum);


    //QTimer to help move Pillar with time
    QTimer *timer_move = new QTimer(this);

    //connect (first_object,SIGNAL,second_object,SLOT)
    connect (timer_move,SIGNAL(timeout()),this,SLOT(move()));

    //Restart timer after every 20 mili-seconds
    timer_move->start(10);
}

void Pillar::move(){
     setPos(x()-2,y());

     //if a bullet collides with an enemy destroy both
     //colliding item returns a list of coliding object
         QList<QGraphicsItem *> Bullet_colliding_Pillar = collidingItems();
     //traversing the list
         for (int i = 0, n = Bullet_colliding_Pillar.size();i < n; ++i)
     {
         if(typeid(*(Bullet_colliding_Pillar[i])) == typeid(Bullet))
         {
            this->hp -= 25;
            scene()->removeItem(Bullet_colliding_Pillar[i]);
            delete Bullet_colliding_Pillar[i];

            if(this->hp <= 0)
            {
            //remove them both

                scene()->removeItem(this);
            //delete them both free the memoery from heap

                delete this;
            //returning out of this member function otherwise it will crash
            //When bullet gets destroyed bullet can't move up
                return;
            }
         }
     }




  if(pos().x() <= -(this->length))
  {
    scene()->removeItem(this);
    delete this;
  }

}
