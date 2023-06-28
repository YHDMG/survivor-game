#ifndef PREPARESCENE_H
#define PREPARESCENE_H

#include <QWidget>
#include "gamescene.h"
#include <QLabel>
class prepareScene : public QWidget
{
    Q_OBJECT
public:
    explicit prepareScene(QWidget *parent = nullptr);
    gameScene *game_scene =  nullptr;
signals:
    void backtomain();
};

#endif // PREPARESCENE_H
