#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class enemy :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit enemy(QObject *parent = nullptr);
    enemy(QPoint pos, QPixmap pix, int type);
public:
    int maxhp;
    int hp;
    int atk;
    int def;
    int type;
    int face;
    int movepicture;
    int tox;
    int toy;
    QPixmap pix;
signals:

};

#endif // ENEMY_H
