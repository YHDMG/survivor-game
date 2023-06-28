#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
class MapScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MapScene(QWidget *parent = nullptr)
    {
        setSceneRect(0,0,1920,1080);
    }
signals:

};

#endif // MAPSCENE_H
