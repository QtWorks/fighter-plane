#ifndef PETROL_H
#define PETROL_H
#include <QObject>
#include <QGraphicsPixmapItem>

class Petrol : public QObject, public QGraphicsPixmapItem
{
private:
    Q_OBJECT
    int pos_x;
    int pos_y;
    int length;
    int height;
public:
    Petrol();

public slots:
    void move();
};

#endif // PETROL_H
