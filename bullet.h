#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>


class bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum bullettype
    {
        player,
        enemy
    };
    explicit bullet(QObject *parent = nullptr);
    bullet(QPoint pos, QPixmap pix, int type, QPoint point, int range);
    void bulletmove();


    QPoint point;
    int mtype;
    int life;
    int damage;
signals:

};

#endif // BULLET_H
