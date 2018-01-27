#ifndef PILLAR_H
#define PILLAR_H

//QGraphicsRectItem Create Rectangles
#include <QGraphicsPixmapItem>


//QObject Library included to pass on Object Properties, Connect Via Signal and Slots
#include <QObject>

//Reactangle Pillars Inheriting from QObject and QGraphicsRectItem
class Pillar:public QObject,public QGraphicsPixmapItem
{
private:
    //Helps to add Connect Signal and Slot
    Q_OBJECT
    int pos_x;
    int pos_y;
    int length;
    int height;
    int hp;
public:
    Pillar();

public slots:
    //Move Function will be Connected with Time
    void move();
};

#endif // PILLAR_H
