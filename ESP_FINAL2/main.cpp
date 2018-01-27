#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QGraphicsRectItem>
#include <stdlib.h>
#include <QTimer>
#include <QMediaPlayer>
#include <QImage>
#include <QBrush>
#include "pillar.h"
#include "plane.h"
#include "petrol.h"

int main(int argc, char *argv[])
{
    QApplication FlappyPlane(argc, argv);

    //Create Scene (Abstract)
    QGraphicsScene *WindowScene = new QGraphicsScene();

    //Visualize the WindowScene (Abstract) on Screen
    QGraphicsView *VisualizeWindowScene = new QGraphicsView(WindowScene);
    //ui->VisualizeWindowScene->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    int x[2] = {0,800};
    int y[2] = {-50,625};

    //WindowScene Position and Size
    WindowScene->setSceneRect(x[0],y[0],x[1],y[1]);
    VisualizeWindowScene->setFixedSize(x[1],y[1]);

    //Turn Off Scroll Bars of VisualizeWindowScene
    VisualizeWindowScene->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    VisualizeWindowScene->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Background Image
    WindowScene->setBackgroundBrush(QBrush(QImage(":/images/Backgroundimage.jpg")));

//    //Plays background music
//    QMediaPlayer *bgmusic = new QMediaPlayer();
//    bgmusic->setMedia(QUrl("qrc:/sounds/backgroundSound.mp3"));
//    bgmusic->play();
//    bgmusic->setVolume(100);

    //Boundary Rectangle
    QGraphicsRectItem *boundaryRect = new QGraphicsRectItem(0,0,797,570);
    WindowScene->addItem(boundaryRect);

    //Flappy Plane
    Plane *flappyPlane = new Plane();
    flappyPlane->setFlag(QGraphicsItem::ItemIsFocusable);
    flappyPlane->setFocus();
    WindowScene->addItem(flappyPlane);
    //flappyPlane->setPos(VisualizeWindowScene->x()+flappyPlane->rect().width(),VisualizeWindowScene->height()/2);

    //Remaining Fuel
    flappyPlane->fuelText->setDefaultTextColor(Qt::white);
    WindowScene->addItem(flappyPlane->fuelText);

    //Remaining Bullets
    flappyPlane->ammoText->setDefaultTextColor(Qt::white);
    WindowScene->addItem(flappyPlane->ammoText);

    //Player's score
    flappyPlane->scoreText->setDefaultTextColor(Qt::white);
    WindowScene->addItem(flappyPlane->scoreText);

    //Timer for pillar to spawn
    QTimer * timer_pillar = new QTimer();
    QObject::connect(timer_pillar,SIGNAL(timeout()),flappyPlane,SLOT(spawn_pillar()));
    timer_pillar->start(900);

    //Timer for petrol to spawn
    QTimer * timer_petrol = new QTimer();
    QObject::connect(timer_petrol,SIGNAL(timeout()),flappyPlane,SLOT(spawn_petrol()));
    timer_petrol->start(2000);

    //Displays
    VisualizeWindowScene->show();
    return FlappyPlane.exec();
}
