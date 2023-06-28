#ifndef LOOT_H
#define LOOT_H

#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
class loot :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit loot(QWidget *parent = nullptr);
    loot(QPoint pos, QPixmap pix, int type);
    int type;
};

#endif // LOOT_H
