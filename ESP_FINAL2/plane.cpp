#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QMediaPlayer>
#include "pillar.h"
#include "petrol.h"
#include "plane.h"
#include "bullet.h"


Plane::Plane():QGraphicsPixmapItem()
{
    plane_x_pos = 0;
    plane_y_pos = 0;
    plane_length = 75;
    plane_height= 50 ;

    fuel = 100;
    ammo = 12;
    score = 0.0;

    explosionFlag = 0;

    setPixmap(QPixmap(":/images/plane.png"));
    setPos(50,200);

    //QTimer to help move Pillar with time
    QTimer *timer_move = new QTimer(this);

    //connect (first_object,SIGNAL,second_object,SLOT)
    connect (timer_move,SIGNAL(timeout()),this,SLOT(move()));

    //Restart timer after every 100 mili-seconds
    timer_move->start(100);
    gravity_effect = 1;

    //Timer for ammo increment
    QTimer *timer_ammo = new QTimer(this);
    connect(timer_ammo,SIGNAL(timeout()),this,SLOT(ammo_increment()));
    timer_ammo->start(5000);

    //Text for displaying fuel
    fuelText = new QGraphicsTextItem();
    fuelText->setPlainText(QString("Fuel: ") + QString::number(this->fuel));
    fuelText->setPos(700,-40);

    //Text for displaying ammo
    ammoText = new QGraphicsTextItem();
    ammoText->setPlainText(QString("Ammo: ") + QString::number(this->ammo));
    ammoText->setPos(400,-40);

    //Test for displaying score
    scoreText = new QGraphicsTextItem();
    scoreText->setPlainText(QString("Score: ") + QString::number((int)this->score));
    scoreText->setPos(100,-40);

    //Timer for playing background music
    QTimer *timer_bgmusic = new QTimer();
    connect(timer_bgmusic,SIGNAL(timeout()),this,SLOT(playBgMusic()));
    timer_bgmusic->start(35000);

    //Plays background music for the first time
    QMediaPlayer *bgmusic = new QMediaPlayer();
    bgmusic->setMedia(QUrl("qrc:/sounds/backgroundSound.mp3"));
    bgmusic->setVolume(100);
    bgmusic->play();
}

void Plane::playBgMusic()
{
    //After every 35 seconds, replays the background music
    QMediaPlayer *bgmusic = new QMediaPlayer();
    bgmusic->setMedia(QUrl("qrc:/sounds/backgroundSound.mp3"));
    bgmusic->setVolume(100);
    bgmusic->play();
}

void Plane::spawn_pillar(){
    Pillar *pillar1 = new Pillar();

    scene()->addItem(pillar1);
}

void Plane::spawn_petrol(){
    Petrol *petrol1 = new Petrol();

    scene()->addItem(petrol1);
}

void Plane::ammo_increment()
{
    this->ammo += 3;
}

void Plane::fuel_plane()
{
    fuelText->setPlainText(QString("Fuel: ") + QString::number(this->fuel));
}

void Plane::ammo_plane()
{
   ammoText->setPlainText(QString("Ammo: ") + QString::number(this->ammo));
}

void Plane::score_plane()
{
   scoreText->setPlainText(QString("Score: ") + QString::number((int)this->score));
}

void Plane::move()
{
    fuel -= 1;
    score+= 0.5;

    fuel_plane();
    ammo_plane();
    score_plane();

    //qDebug() << "Fuel: " << fuel << endl;


    if (fuel <= 0)
    {
        explosionFlag = 1;

        QMediaPlayer *planeExplosion_sound = new QMediaPlayer();
        planeExplosion_sound->setMedia(QUrl("qrc:/sounds/planeExplosion.mp3"));
        planeExplosion_sound->play();
        planeExplosion_sound->setVolume(75);

        //Displays the explosion image
        QGraphicsPixmapItem *planeExplosion_image = new QGraphicsPixmapItem();
        planeExplosion_image->setPixmap(QPixmap(":/images/planeExplosion.png"));
        planeExplosion_image->setPos(this->x(),this->y());
        scene()->addItem(planeExplosion_image);

        scene()->removeItem(this);
        delete this;
        return;
    }

    //qDebug() << "Ammo: " << this->ammo << endl;

    //qDebug() << "Plane's y" << this->y() << endl;
    if (this->y() < this->plane_y_pos)
    {
        setPos(x(),this->plane_y_pos);
    }
    else if (this->y() + this->plane_height >= (570))
    {
        explosionFlag = 1;

        //Plays the plane explosion sound
        QMediaPlayer *planeExplosion_sound = new QMediaPlayer();
        planeExplosion_sound->setMedia(QUrl("qrc:/sounds/planeExplosion.mp3"));
        planeExplosion_sound->play();
        planeExplosion_sound->setVolume(75);

        //Displays the explosion image
        QGraphicsPixmapItem *planeExplosion_image = new QGraphicsPixmapItem();
        planeExplosion_image->setPixmap(QPixmap(":/images/planeExplosion.png"));
        planeExplosion_image->setPos(this->x(),this->y());
        scene()->addItem(planeExplosion_image);

        //Removes item from scene
        scene()->removeItem(this);
        delete this;
        return;
    }
    else
    {
        setPos(x(),y()+ 1 + (gravity_effect+=2));
    }


    //Plane collding with pillar
    QList<QGraphicsItem *> Plane_colliding_Pillar = collidingItems();
    for (int i = 0, n = Plane_colliding_Pillar.size();i < n; ++i)
    {
       if(typeid(*(Plane_colliding_Pillar[i])) == typeid(Pillar))
       {
           //Plays the plane explosion sound
           QMediaPlayer *planeExplosion_sound = new QMediaPlayer();
           planeExplosion_sound->setMedia(QUrl("qrc:/sounds/planeExplosion.mp3"));
           planeExplosion_sound->play();
           planeExplosion_sound->setVolume(75);

           //Displays the explosion image
           QGraphicsPixmapItem *planeExplosion_image = new QGraphicsPixmapItem();
           planeExplosion_image->setPixmap(QPixmap(":/images/planeExplosion.png"));
           planeExplosion_image->setPos(this->x(),this->y());
           scene()->addItem(planeExplosion_image);

           //scene()->removeItem(planeExplosion_image);

           //removes both items
           scene()->removeItem(Plane_colliding_Pillar[i]);
           scene()->removeItem(this);
           delete Plane_colliding_Pillar[i];
           delete this;
           return;
       }
    }

    //Plane colliding with petrol bubble
    QList<QGraphicsItem *> Petrol_colliding_Plane = collidingItems();
    //traversing the list
    for (int i = 0, n = Petrol_colliding_Plane.size();i < n; ++i)
    {
        if(typeid(*(Petrol_colliding_Plane[i])) == typeid(Petrol))
        {
            //Plays the bubble pop sound
            QMediaPlayer *petrolBubblePop = new QMediaPlayer();
            petrolBubblePop->setMedia(QUrl("qrc:/sounds/fuelBubblePop.mp3"));
            petrolBubblePop->play();
            petrolBubblePop->setVolume(100);

            //increments the score
            this->score+=5.0;

            if(this->fuel > 50.0)
            {
                this->fuel = this->fuel + (100 - this->fuel);
            }
            else
            {
                this->fuel += 50.0;
            }

            //delete them both free the memoery from heap
            scene()->removeItem(Petrol_colliding_Plane[i]);
            delete Petrol_colliding_Plane[i];
        }
    }
}

void Plane::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Up)
    {
        if (this->y() > 0 && this->y() <= 545)
        {
           gravity_effect= 1;
           setPos(x(),y()-20);
        }
    }

    if (event->key() == Qt::Key_Space)
    {
        if (this->ammo > 0)
        {
            Bullet *bullet1 = new Bullet();
            bullet1->setPos(x()+this->plane_length,y()+(plane_height / 2));
            scene()->addItem(bullet1);

            //Plays the bullet fire sound
            QMediaPlayer *bulletfire = new QMediaPlayer();
            bulletfire->setMedia(QUrl("qrc:/sounds/bulletFire.mp3"));
            bulletfire->play();
            bulletfire->setVolume(70);

            this->ammo--;
        }
   }
}
