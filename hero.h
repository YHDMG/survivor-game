#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class hero :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit hero();
    int maxhp;
    int hp;
    int atk;
    int def;
    int shotspeed;
    int movespeed;
    int movepicture;
    int face;
    int level;
    int maxexp;
    int exp;
    int waepen;
    int range;
    int iframe;
    int gold;
    int goldgain;
    int revive;

};

#endif // HERO_H
