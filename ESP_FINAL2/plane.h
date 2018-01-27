#ifndef PLANE_H
#define PLANE_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Plane : public QObject,public QGraphicsPixmapItem
{
    //Helps to add Connect Signal and Slot
    Q_OBJECT
private:
    int plane_x_pos;
    int plane_y_pos;
    int plane_length;
    int plane_height;
    int fuel;
    int ammo;
    float score;
    int gravity_effect;
    int explosionFlag;

public:
    Plane();
    QGraphicsTextItem *fuelText;
    QGraphicsTextItem *ammoText;
    QGraphicsTextItem *scoreText;

    //receiving event
    void keyPressEvent(QKeyEvent *event);
    void fuel_plane();
    void ammo_plane();
    void score_plane();

public slots:
    void playBgMusic();
    void spawn_pillar();
    void spawn_petrol();
    void ammo_increment();

    void move();

};

#endif // PLANE_H
