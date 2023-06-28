#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "hero.h"
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QtGlobal>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "bullet.h"
#include "enemy.h"
#include <QMediaPlayer>
#include <QLabel>
#include "loot.h"
#include "button.h"
class gameScene : public QWidget
{
    Q_OBJECT
public:
    explicit gameScene(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void startgame();
    void gamepause();
    void updateLabel();
    void dead();
    void levelUp();
    void savedata();
    void readdata(int x);
    int random(int begin, int limit);
    int distance(int x, int y, int tx, int ty);
    hero player;
private:

    int gameTime;
    int difficulty;

    bool up;
    bool down;
    bool left;
    bool right;
    bool isrunning;

    button* button_back;
    button* button_continue;
    button* hpup;
    button* atkup;
    button* defup;
    button* rangeup;
    button* shotspeedup;

    QTimer* mainTimer;
    QTimer* moveTimer;
    QTimer* shotTimer;
    QTimer* enemyShootTimer;
    QTimer* bulletMoveTimer;
    QTimer* enemyGenerateTimer1;
    QTimer* enemyGenerateTimer2;
    QTimer* enemyGenerateTimer3;
    QTimer* enemyMoveTimer;
    QTimer* collisionTimer;
    QTimer* iframeTimer;
    QTimer* moveanimeTimer;

    QPixmap playerPix;
    QPixmap bulletPix;
    QPixmap enemyPix;
    QPixmap expballPix;
    QPixmap shellPix;

    QGraphicsView mView;
    QGraphicsScene mScene;
    QGraphicsScene mStart;
    QGraphicsPixmapItem background;

    QLabel* hpLabel;
    QLabel* levelLabel;
    QLabel* atkLabel;
    QLabel* defLabel;
    QLabel* stspdLabel;
    QLabel* rangeLabel;
    QLabel* timeLabel;
    QLabel* pausedBackgroundLabel;
    QLabel* shellLabel;
    QLabel* stoneLabel;
    QLabel* goldLabel;
    QLabel* gameoverLabel;
    QLabel* winLabel;

    QList<bullet*> bulletList;
    QList<bullet*> enemybulletList;
    QList<enemy*> enemyList;
    QList<loot*> lootList;
    QList<enemy*> stoneList;
    QList<button*> levelUpList;

    QMediaPlayer* mBG;
    QMediaPlayer* mBulletSound;
signals:
    void backtomain();
};

#endif // GAMESCENE_H
