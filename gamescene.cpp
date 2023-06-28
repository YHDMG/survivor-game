#include "gamescene.h"
#include "button.h"
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QRect>
#include "bullet.h"
#include <QTime>
#include <QtMath>
#include <QSettings>
gameScene::gameScene(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1920,1080);//设置窗口分辨率
    this->setWindowTitle("神秘的幸存者");//设置窗口标题
    //this->setWindowIcon();设置应用图片 no picture now :(

    //背景音乐
    this->mBG = new QMediaPlayer(this);
    this->mBG->setMedia(QUrl("qrc:/8bit.mp3"));
    this->mBG->setVolume(2);

    //子弹发射音效
    this->mBulletSound = new QMediaPlayer(this);
    this->mBulletSound->setMedia(QUrl("qrc:/bullet.mp3"));
    this->mBulletSound->setVolume(1);

    //界面设置与图片加载
    mScene.setSceneRect(QRect(0,0,1920,1080));
    mView.setSceneRect(QRect(0,0,1920,1080));
    background.setPixmap(QPixmap(":/map.png"));
    background.setPos(-2880,-1620);
    bulletPix.load(":/bullet.png");
    expballPix.load(":/expball.png");
    mScene.addItem(&background);


    //玩家加载
    player.setPixmap(QPixmap(":/playerd2.png"));
    player.setPos(960,540);
    mScene.addItem(&player);

    //设置场景并显示
    mView.setScene(&mScene);
    mView.setParent(this);
    mView.show();

    //各种状态判断
    isrunning = 0;
    up = 0;
    down = 0;
    left = 0;
    right = 0;

    //设置字体
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::black);
    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    QFont font2;
    font.setPointSize(12);
    font.setBold(true);

    //基础属性显示设置
    //血量
    hpLabel=new QLabel(this);
    hpLabel->setFixedSize(120,80);
    hpLabel->move(20,20);
    hpLabel->setPalette(palette);
    hpLabel->setFont(font);
    hpLabel->show();
    //等级
    levelLabel=new QLabel(this);
    levelLabel->setFixedSize(180,80);
    levelLabel->move(180,20);
    levelLabel->setPalette(palette);
    levelLabel->setFont(font);
    levelLabel->show();
    //时间
    timeLabel=new QLabel(this);
    timeLabel->setFixedSize(180,80);
    timeLabel->move(990,20);
    timeLabel->setPalette(palette);
    timeLabel->setFont(font);
    timeLabel->show();

    //其余属性显示
    //攻击力
    atkLabel=new QLabel(this);
    atkLabel->setFixedSize(180,80);
    atkLabel->move(20,100);
    atkLabel->setPalette(palette);
    atkLabel->setFont(font);
    atkLabel->show();
    //防御力
    defLabel=new QLabel(this);
    defLabel->setFixedSize(180,80);
    defLabel->move(20,120);
    defLabel->setPalette(palette);
    defLabel->setFont(font);
    defLabel->show();
    //子弹射速
    stspdLabel=new QLabel(this);
    stspdLabel->setFixedSize(180,80);
    stspdLabel->move(20,140);
    stspdLabel->setPalette(palette);
    stspdLabel->setFont(font);
    stspdLabel->show();
    //子弹射程
    rangeLabel=new QLabel(this);
    rangeLabel->setFixedSize(180,80);
    rangeLabel->move(20,160);
    rangeLabel->setPalette(palette);
    rangeLabel->setFont(font);
    rangeLabel->show();
    //金币数量
    goldLabel=new QLabel(this);
    goldLabel->setFixedSize(180,80);
    goldLabel->move(20,180);
    goldLabel->setPalette(palette);
    goldLabel->setFont(font);
    goldLabel->show();
    //游戏结束
    gameoverLabel=new QLabel(this);
    gameoverLabel->move(this->width() * 0.5 - QPixmap(":/gameover.png").width() * 0.5,200);
    gameoverLabel->setPixmap(QPixmap(":/gameover.png"));
    gameoverLabel->hide();
    //游戏胜利
    winLabel=new QLabel(this);
    winLabel->move(this->width() * 0.5 - QPixmap(":/win.png").width() * 0.5,200);
    winLabel->setPixmap(QPixmap(":/win.png"));
    winLabel->hide();
    //护盾
    shellLabel = new QLabel(this);
    shellPix.load(":/shell.png");
    shellLabel->setPixmap(shellPix);
    shellLabel->setScaledContents(true);
    shellLabel->move(940,520);
    shellLabel->hide();

    //暂停显示设置
    pausedBackgroundLabel=new QLabel(this);
    pausedBackgroundLabel->setPixmap(QPixmap(tr(":/pausedbackground.png")));
    pausedBackgroundLabel->setScaledContents(true);
    pausedBackgroundLabel->move(0,0);
    pausedBackgroundLabel->hide();

    //返回主界面
    button_back = new button;
    button_back->setParent(this);
    button_back->setIMage(":/pause-back.png",":/pause-back.png",":/pause-back.png");
    button_back->move(this->width() * 0.5 - button_back->width() * 0.5,700);
    connect(button_back, &button::clicked, [=]()
    {
        this->mBG->stop();
        emit this->backtomain();
    });
    button_back->hide();

    //继续游戏
    button_continue = new button;
    button_continue->setParent(this);
    button_continue->setIMage(":/pause-continue.png",":/pause-continue.png",":/pause-continue.png");
    button_continue->move(this->width() * 0.5 - button_continue->width() * 0.5,500);
    connect(button_continue, &button::clicked, [=]()
    {
        QTimer::singleShot(200,[=]()
        {
            button_back->hide();
            button_continue->hide();
            pausedBackgroundLabel->hide();
            gamepause();
        });
    });
    button_continue->hide();

    //升级强化按钮
    //血量
    hpup = new button;
    hpup->setParent(this);
    hpup->setIMage(":/hp.png",":/hp.png",":/hp.png");
    hpup->move(500,700);
    connect(hpup, &button::clicked, [=]()
    {
        player.maxhp += 20;
        levelUp();
    });
    hpup->hide();
    //攻击
    atkup = new button;
    atkup->setParent(this);
    atkup->setIMage(":/atk.png",":/atk.png",":/atk.png");
    atkup->move(650,700);
    connect(atkup, &button::clicked, [=]()
    {
        player.atk += 10;
        levelUp();
    });
    atkup->hide();
    //防御
    defup = new button;
    defup->setParent(this);
    defup->setIMage(":/def.png",":/def.png",":/def.png");
    defup->move(800,700);
    connect(defup, &button::clicked, [=]()
    {
        player.def += 5;
        levelUp();
    });
    defup->hide();
    //射程
    rangeup = new button;
    rangeup->setParent(this);
    rangeup->setIMage(":/range.png",":/range.png",":/range.png");
    rangeup->move(950,700);
    connect(rangeup, &button::clicked, [=]()
    {
        player.range += 50;
        levelUp();
    });
    rangeup->hide();
    //射速
    shotspeedup = new button;
    shotspeedup->setParent(this);
    shotspeedup->setIMage(":/shotspeed.png",":/shotspeed.png",":/shotspeed.png");
    shotspeedup->move(1100,700);
    connect(shotspeedup, &button::clicked, [=]()
    {
        player.shotspeed -= 30;
        levelUp();
    });
    shotspeedup->hide();

    levelUpList.append(hpup);
    levelUpList.append(atkup);
    levelUpList.append(defup);
    levelUpList.append(rangeup);
    levelUpList.append(shotspeedup);

    //总游戏倒计时
    gameTime = 0;
    difficulty = 1;
    mainTimer = new QTimer(this);
    connect(mainTimer,&QTimer::timeout, [=]()
    {
        gameTime++;
        difficulty++;
        savedata();
        if(gameTime == 60)
        {
            isrunning = 0;
            winLabel->show();
            pausedBackgroundLabel->show();
            button_back->show();
            QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
            if(setting.contains(tr("Global reinforcement/used")))
            {
                int gold = setting.value("Global reinforcement/gold").toInt();
                setting.setValue("Global reinforcement/gold", player.gold + gold);
                setting.sync();
            }


        }
        //游戏结束
    });

    //玩家移动
    moveTimer = new QTimer(this);
    connect(moveTimer,&QTimer::timeout, [=]()
    {
        if(isrunning )
        {
            if(up == 1 &&  background.y() <= 0 )
                background.moveBy(0,player.movespeed);
            if(down == 1 && background.y()  >= -1080-1620 )
                background.moveBy(0,-player.movespeed);
            if(left == 1 &&  background.x()  <= 0)
                background.moveBy(player.movespeed,0);
            if(right == 1 &&  background.x() >= -1920-2880)
                background.moveBy(-player.movespeed,0);

        }
    });

    //移动动画
    moveanimeTimer = new QTimer(this);
    connect(moveanimeTimer,&QTimer::timeout, [=]()
    {
        if(isrunning )
        {
            //玩家动画
            if(player.face == 1)
            {
                if(player.movepicture != 3 && player.movepicture != 4 && player.movepicture != 5 )
                {
                    player.setPixmap(QPixmap(":/playerrw2.png"));
                    player.movepicture = 4;
                }
                else if(player.movepicture == 4)
                {
                    player.setPixmap(QPixmap(":/playerrw3.png"));
                    player.movepicture = 5;
                }
                else if(player.movepicture == 5)
                {
                    player.setPixmap(QPixmap(":/playerrw1.png"));
                    player.movepicture = 3;
                }
                else if(player.movepicture == 3)
                {
                    player.setPixmap(QPixmap(":/playerrw2.png"));
                    player.movepicture = 4;
                }
            }
            else if(player.face == 5)
            {
                if(player.movepicture != 0 && player.movepicture != 1 && player.movepicture != 2 )
                {
                    player.setPixmap(QPixmap(":/playerd2.png"));
                    player.movepicture = 1;
                }
                else if(player.movepicture == 1)
                {
                    player.setPixmap(QPixmap(":/playerd3.png"));
                    player.movepicture = 2;
                }
                else if(player.movepicture == 2)
                {
                    player.setPixmap(QPixmap(":/playerd1.png"));
                    player.movepicture = 0;
                }
                else if(player.movepicture == 0)
                {
                    player.setPixmap(QPixmap(":/playerd2.png"));
                    player.movepicture = 1;
                }
            }
            else if(player.face == 3)
            {
                if(player.movepicture != 6 && player.movepicture != 7 && player.movepicture != 8 )
                {
                    player.setPixmap(QPixmap(":/playerr2.png"));
                    player.movepicture = 7;
                }
                else if(player.movepicture == 7)
                {
                    player.setPixmap(QPixmap(":/playerr3.png"));
                    player.movepicture = 8;
                }
                else if(player.movepicture == 8)
                {
                    player.setPixmap(QPixmap(":/playerr1.png"));
                    player.movepicture = 6;
                }
                else if(player.movepicture == 6)
                {
                    player.setPixmap(QPixmap(":/playerr2.png"));
                    player.movepicture = 7;
                }
            }
            else if(player.face == 7)
            {
                if(player.movepicture != 9 && player.movepicture != 10 && player.movepicture != 11 )
                {
                    player.setPixmap(QPixmap(":/playerl2.png"));
                    player.movepicture = 10;
                }
                else if(player.movepicture == 10)
                {
                    player.setPixmap(QPixmap(":/playerl3.png"));
                    player.movepicture = 11;
                }
                else if(player.movepicture == 11)
                {
                    player.setPixmap(QPixmap(":/playerl1.png"));
                    player.movepicture = 9;
                }
                else if(player.movepicture == 9)
                {
                    player.setPixmap(QPixmap(":/playerl2.png"));
                    player.movepicture = 10;
                }
            }
        }
    });


    //发射子弹
    shotTimer = new QTimer(this);
    connect(shotTimer,&QTimer::timeout, [=]()
    {
        //qDebug() << player.shotspeed << endl;
        if(isrunning)
        {
            //单发
            if(player.waepen == 0)
            {
                this->mBulletSound->play();
                QPoint bulletpos ( player.x() - background.x() + player.pixmap().width() / 2 - bulletPix.width() / 2 , player.y() - background.y() + player.pixmap().height() / 2 - bulletPix.height() / 2 );
        //        qDebug() << bulletpos.x()  << endl;
                QPoint  mpoint;
//                qDebug() << player.face << endl;
                if(player.face == 1)
                    mpoint = QPoint(0,-10);
                else if(player.face == 5)
                    mpoint = QPoint(0,10);
                else if(player.face == 3)
                    mpoint = QPoint(10,0);
                else if(player.face == 7)
                    mpoint = QPoint(-10,0);
                bullet * b = new bullet(bulletpos,bulletPix,bullet::player,mpoint,player.range);
                b->setParentItem(&background);
                mScene.addItem(b);
                bulletList.append(b);
            }
            //散射
            else if(player.waepen == 1)
            {
                this->mBulletSound->play();
                QPoint bulletpos ( player.x() - background.x() + player.pixmap().width() / 2 - bulletPix.width() / 2 , player.y() - background.y() + player.pixmap().height() / 2 - bulletPix.height() / 2 );
        //        qDebug() << bulletpos.x()  << endl;
                QPoint  mpoint1;
                QPoint  mpoint2;
                QPoint  mpoint3;
//                qDebug() << player.face << endl;
                if(player.face == 1)
                {
                    mpoint1 = QPoint(0,-5);
                    mpoint2 = QPoint(-1,-5);
                    mpoint3 = QPoint(1,-5);
                }
                else if(player.face == 5)
                {
                    mpoint1 = QPoint(0,5);
                    mpoint2 = QPoint(-1,5);
                    mpoint3 = QPoint(1,5);
                }
                else if(player.face == 3)
                {
                    mpoint1 = QPoint(5,0);
                    mpoint2 = QPoint(5,1);
                    mpoint3 = QPoint(5,-1);
                }
                else if(player.face == 7)
                {
                    mpoint1 = QPoint(-5,0);
                    mpoint2 = QPoint(-5,1);
                    mpoint3 = QPoint(-5,-1);
                }
                bullet * b1 = new bullet(bulletpos,bulletPix,bullet::player,mpoint1,player.range);
                bullet * b2 = new bullet(bulletpos,bulletPix,bullet::player,mpoint2,player.range);
                bullet * b3 = new bullet(bulletpos,bulletPix,bullet::player,mpoint3,player.range);
                b1->setParentItem(&background);
                b2->setParentItem(&background);
                b3->setParentItem(&background);
                mScene.addItem(b1);
                mScene.addItem(b2);
                mScene.addItem(b3);
                bulletList.append(b1);
                bulletList.append(b2);
                bulletList.append(b3);

            }

        }
    });

    //怪物子弹
    enemyShootTimer = new QTimer(this);
    connect(enemyShootTimer,&QTimer::timeout, [=]()
    {
        if(isrunning)
        {
            for(auto i = enemyList.begin() ; i != enemyList.end() ; i++)
            {
                if((*i)->type == 2)
                {
                    int s = distance((*i)->pos().x(),(*i)->pos().y(), player.x() - background.x(),player.y() - background.y());
                    int x = -5 * abs((player.x() - background.x() - (*i)->pos().x())) / s;
                    int y = -5 * abs((player.y() - background.y() - (*i)->pos().y())) / s;
                    if((player.x() - background.x() - (*i)->pos().x()) == 0)
                    {
                        x = 0;
                        y = -3;
                    }
                    if((player.y() - background.y() - (*i)->pos().y()) == 0)
                    {
                        y = 0;
                        x = -3;
                    }
                    if((player.x() - background.x() - (*i)->pos().x()) > 0)
                         x *= -1;
                    if((player.y() - background.y() - (*i)->pos().y()) > 0)
                         y *= -1;
                    QPoint enemypos = QPoint( (*i)->pos().x() , (*i)->pos().y());
                    QPoint  mpoint(x,y);
                    bullet * b = new bullet(enemypos,bulletPix,bullet::enemy,mpoint,1000);
                    b->setParentItem(&background);
                    mScene.addItem(b);
                    enemybulletList.append(b);
                }
            }

        }
    });


    //子弹移动
    bulletMoveTimer = new QTimer(this);
    connect(bulletMoveTimer, &QTimer::timeout, [=]()
    {
        if(isrunning)
        {
            for(auto i = bulletList.begin() ; i != bulletList.end() ; i++)
            {
                (*i)->bulletmove();
                (*i)->life--;
                if((*i)->life <= 0)
                {
                    mScene.removeItem((*i));
                    bulletList.erase(i);
                }
            }

            for(auto i = enemybulletList.begin() ; i != enemybulletList.end() ; i++)
            {
                (*i)->bulletmove();
                (*i)->life--;
                if((*i)->life <= 0)
                {
                    mScene.removeItem((*i));
                    enemybulletList.erase(i);
                }
            }
        }
    });

    //怪物类型1生成
    enemyGenerateTimer1 = new QTimer(this);
    connect(enemyGenerateTimer1,&QTimer::timeout, [=]()
    {
        if(isrunning)
        {
        QPoint pos(player.x() - background.x() - random(-1920,1920) ,player.y() - background.y() - random(-1080, 1080));
        QPixmap pix;
        if(player.x() - background.x() - pos.x() >= 0)
            pix = QPixmap(":/slm2.png");
        else
            pix = QPixmap(":/slm2f.png");
        enemy *e = new enemy(pos,pix,0);
        e->setParentItem(&background);
        mScene.addItem(e);
        enemyList.append(e);
        }
    });

    //怪物类型2生成
    enemyGenerateTimer2 = new QTimer(this);
    connect(enemyGenerateTimer2,&QTimer::timeout, [=]()
    {
        if(isrunning)
        {
        QPoint pos(player.x() - background.x() - random(-960,960) ,player.y() - background.y() - random(-540, 540));
        QPixmap pix;
        if(player.x() - background.x() - pos.x() >= 0)
            pix = QPixmap(":/slm2.png");
        else
            pix = QPixmap(":/slm2f.png");
        enemy *e = new enemy(pos,pix,1);
        e->face = enemyList.size() % 4;
        e->setParentItem(&background);
        mScene.addItem(e);
        enemyList.append(e);

        }
    });

    //怪物类型3生成
    enemyGenerateTimer3 = new QTimer(this);
    connect(enemyGenerateTimer3,&QTimer::timeout, [=]()
    {
        if(isrunning)
        {
        QPoint pos(player.x() - background.x() - random(-960,960) ,player.y() - background.y() - random(-540, 540));
        enemy *e = new enemy(pos,enemyPix,2);
        e->setParentItem(&background);
        mScene.addItem(e);
        enemyList.append(e);
        }
    });

    //怪物类型4（障碍物）生成
    for(int i = 1; i <= 10 ; i++)
    {
        QPoint pos(player.x() - background.x() - random(-1920,1920) ,player.y() - background.y() - random(-1080, 1080));
        enemy *e = new enemy(pos,QPixmap(":/stone.png"),0);
        e->hp = 5000;
        e->setParentItem(&background);
        mScene.addItem(e);
        stoneList.append(e);
    }


    //怪物移动
    enemyMoveTimer = new QTimer(this);
    connect(enemyMoveTimer, &QTimer::timeout, [=]()
    {
        if(isrunning)
        {
            for(auto i = enemyList.begin() ; i != enemyList.end() ; i++)
            {
                //追踪角色
                if( (  (*i)->type == 0 || (*i)->type == 2 ))
                {
                        //qDebug() << player.x() << backgrand.x() << (*i)->pos().x() << endl;
                        int s = distance((*i)->pos().x(),(*i)->pos().y(), player.x() - background.x(),player.y() - background.y());
                        int x = -5 * abs((player.x() - background.x() - (*i)->pos().x())) / s;
                        int y = -5 * abs((player.y() - background.y() - (*i)->pos().y())) / s;
                        if((player.x() - background.x() - (*i)->pos().x()) == 0)
                        {
                            x = 0;
                            y = -3;
                        }
                        if((player.y() - background.y() - (*i)->pos().y()) == 0)
                        {
                            y = 0;
                            x = -3;
                        }
                        if((player.x() - background.x() - (*i)->pos().x()) > 0)
                             x *= -1;
                        if((player.y() - background.y() - (*i)->pos().y()) > 0)
                             y *= -1;
                        if(x >= 0)
                        {
                            if( (*i)->movepicture != 1 )
                            {
                                (*i)->setPixmap(QPixmap(":/slm3.png"));
                                (*i)->movepicture = 1;
                            }
                            else
                            {
                                (*i)->setPixmap(QPixmap(":/slm2.png"));
                                (*i)->movepicture = 0;
                            }
                        }
                        else
                        {
                            if( (*i)->movepicture != 2 )
                            {
                                (*i)->setPixmap(QPixmap(":/slm3f.png"));
                                (*i)->movepicture = 3;
                            }
                            else
                            {
                                (*i)->setPixmap(QPixmap(":/slm2f.png"));
                                (*i)->movepicture = 2;
                            }
                        }
                        (*i)->tox = x;
                        (*i)->toy = y;
                        (*i)->moveBy(x,y);
                }
                //直线行走
                else if((*i)->type == 1  )
                {
//                    qDebug() << (*i)->pos().x() << (*i)->pos().y();
                    if((*i)->face == 0)
                    {
                        (*i)->moveBy(10,0);
                        (*i)->tox = 10;
                        (*i)->toy = 0;
                    }
                    else if((*i)->face == 1)
                    {
                        (*i)->moveBy(0,10);
                        (*i)->tox = 0;
                        (*i)->toy = 10;
                    }
                    else if((*i)->face == 2)
                    {
                        (*i)->moveBy(0,-10);
                        (*i)->tox = 0;
                        (*i)->toy = -10;
                    }
                    else if((*i)->face == 3)
                    {
                        (*i)->moveBy(-10,0);
                        (*i)->tox = -10;
                        (*i)->toy = 0;
                    }
                    if((*i)->x() >= 7680 - 1920)
                        (*i)->face = 3;
                    else if((*i)->x() <= 0 + 960)
                        (*i)->face = 0;
                    else if((*i)->y() >= 4320 - 1080)
                        (*i)->face = 2;
                    else if((*i)->y() <= 0 + 540)
                        (*i)->face = 1;
                }
            }
        }
    });


    //碰撞检测
    collisionTimer = new QTimer(this);
    connect(collisionTimer, &QTimer::timeout, [=]()
    {
//            qDebug() << isrunning << endl;
        if(isrunning)
        {
            //子弹命中敌人
            for(int i = 0 ; i < bulletList.size() ; i++)
            {
                for(int j = 0; j < enemyList.size(); j++)
                {
                    if(bulletList[i]->collidesWithItem(enemyList[j]))
                    {
                        if(enemyList[j]->face == 1)
                        {
                            enemyList[j]->setPixmap(QPixmap(":/slm2w.png"));
                            QTimer::singleShot(200,[=]()
                            {
                                enemyList[j]->setPixmap(QPixmap(":/slm2.png"));
                            });
                        }
                        else
                        {
                            enemyList[j]->setPixmap(QPixmap(":/slm2fw.png"));
                            QTimer::singleShot(200,[=]()
                            {
                                enemyList[j]->setPixmap(QPixmap(":/slm2f.png"));
                            });
                        }
                        //qDebug() << 1 << endl;
                        mScene.removeItem(bulletList[i]);
                        bulletList.erase(bulletList.begin() + i);
//                        if(enemyList[j]->face == )
//                        enemyList[j]->setPixmap()
                        enemyList[j]->hp -= player.atk;
                        if(enemyList[j]->hp <= 0)
                        {
                            QPoint pos = (enemyList[j]->pos()).toPoint();
                            QPoint pos2 = QPoint(pos.x() + random(-15,15) , pos.y() + random(-15,15));
                            QPoint pos3 = QPoint(pos.x() + random(-15,15) , pos.y() + random(-15,15));
                             mScene.removeItem(enemyList[j]);
                             enemyList.erase(enemyList.begin() + j);
                             loot *l = new loot(pos,expballPix,0);
                             loot *r = new loot(pos2,QPixmap(":/coin.png"),1);
                             loot *s = new loot(pos3,QPixmap(":/hpball.png"),2);
                     //        qDebug() << e->face << endl;
                             r->setParentItem(&background);
                             mScene.addItem(r);
                             lootList.append(r);
                             s->setParentItem(&background);
                             mScene.addItem(s);
                             lootList.append(s);
                             l->setParentItem(&background);
                             mScene.addItem(l);
                             lootList.append(l);
                        }
                        return ;
                    }
                }
            }
            //拾取掉落物
            for(int i = 0 ; i < lootList.size() ; i++)
            {

                if(player.collidesWithItem(lootList[i]))
                {
                    //qDebug() << 1 << endl;
                    if(lootList[i]->type == 0)
                    {
                        player.exp += 100;
                        if(player.exp >= player.maxexp)
                        {
                            player.level++;
                            player.maxexp += player.level * 100;
                            player.exp = 0;
                            levelUp();
                        }
                    }
                    else if(lootList[i]->type == 1)
                    {
                        player.gold += 5 * player.goldgain;
                        updateLabel();
                    }
                    else if(lootList[i]->type == 2)
                    {
                        if(player.hp + 5 <= player.maxhp)
                            player.hp += 5 ;
                        else
                            player.hp = player.maxhp ;
                        updateLabel();
                    }
                    mScene.removeItem(lootList[i]);
                    lootList.erase(lootList.begin() + i);
                    updateLabel();
                    return ;
                }

            }
            //怪物近战碰撞角色
            for(int i = 0; i < enemyList.size(); i++)
            {
                if(player.collidesWithItem(enemyList[i]) && player.iframe <= 0)
                {
                    if(player.iframe == 0)
                    {
                        shellLabel->show();
                        player.hp -= enemyList[i]->atk - player.def;
                        updateLabel();
                        if(player.hp <= 0)
                        {
                            if(player.revive > 0)
                            {
                                player.revive--;
                                player.hp = player.maxhp;
                            }
                            else
                                dead();
                        }
                        else
                            player.iframe = 5;
                    }
                }

            }
            //怪物子弹碰撞角色
            for(int i = 0; i < enemybulletList.size(); i++)
            {
                if(player.collidesWithItem(enemybulletList[i]) && player.iframe <= 0)
                {
                    if(player.iframe == 0)
                    {
                        shellLabel->show();
                        player.hp -= enemybulletList[i]->damage - player.def;
                        updateLabel();
                        if(player.hp <= 0)
                        {
                            if(player.revive > 0)
                            {
                                player.revive--;
                                player.hp = player.maxhp;
                            }
                            else
                                dead();
                        }
                        else
                            player.iframe = 5;
                    }
                    mScene.removeItem(enemybulletList[i]);
                    enemybulletList.erase(enemybulletList.begin() + i);
                }

            }

            //玩家碰撞障碍物
            for(int i = 0; i < stoneList.size(); i++)
            {
                if(player.collidesWithItem(stoneList[i]))
                {
                    if(left == 1)
                        background.moveBy(-2,0);
                    if(right == 1)
                        background.moveBy(2,0);
                    if(up == 1)
                        background.moveBy(0,-2);
                    if(down == 1)
                        background.moveBy(0,2);
                }
            }

            //怪物碰撞障碍物
            for(int i = 0 ; i < stoneList.size() ; i++)
            {
                for(int j = 0; j < enemyList.size(); j++)
                {
                    if(stoneList[i]->collidesWithItem(enemyList[j]))
                        enemyList[j]->moveBy(-enemyList[j]->tox, -enemyList[j]->toy);

                }
            }
        }
    });

    //无敌帧计时器
    iframeTimer = new QTimer(this);
    connect(iframeTimer,&QTimer::timeout, [=]()
    {
        if(player.iframe > 0)
            player.iframe--;
        if(player.iframe == 0)
            shellLabel->hide();
    });

}


//键盘按下事件
void gameScene::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape)
    {
        if(isrunning)
        {
            this->gamepause();
            pausedBackgroundLabel->show();
            button_back->show();
            button_continue->show();
        }
        else
        {
            pausedBackgroundLabel->hide();
            button_back->hide();
            button_continue->hide();
            this->gamepause();
        }
    }
    if(event->key() == Qt::Key_W)
       up = true;
    if(event->key() == Qt::Key_S)
       down = true;
    if(event->key() == Qt::Key_A)
       left = true;
    if(event->key() == Qt::Key_D)
       right = true;


    if(event->key() == Qt::Key_W )
       player.face = 1;
    else if(event->key() == Qt::Key_S )
       player.face = 5;
    else if(event->key() == Qt::Key_A )
       player.face = 7;
    else if(event->key() == Qt::Key_D )
       player.face = 3;

}

//键盘释放事件
void gameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
        up = false;
    if(event->key() == Qt::Key_S)
        down = false;
    if(event->key() == Qt::Key_A)
        left = false;
    if(event->key() == Qt::Key_D)
        right = false;
}

//开始游戏
void gameScene::startgame()
{
    isrunning = 1;
    mainTimer->start(5000);
    moveTimer->start(5);
    shotTimer->start(player.shotspeed);
    bulletMoveTimer->start(5);
    enemyGenerateTimer1->start(1000-difficulty*10);
    enemyGenerateTimer2->start(5000-difficulty*20);
    enemyGenerateTimer3->start(15000-difficulty*30);
    enemyMoveTimer->start(25);
    collisionTimer->start(5);
    enemyShootTimer->start(2000);
    iframeTimer->start(100);
    moveanimeTimer->start(100);
    button_back->hide();
    button_continue->hide();
    pausedBackgroundLabel->hide();
    updateLabel();
    this->mBG->play();
}

//游戏停止
void gameScene::gamepause()
{
    if(isrunning == 1)
    {
        isrunning = 0;
        this->mBG->setVolume(1);
    }
    else
    {
       isrunning = 1;
       this->mBG->setVolume(2);
    }
}

void gameScene::savedata()
{
    QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
    if(setting.contains(tr("Global reinforcement/used")))
    {
        setting.setValue("Global reinforcement/cr_maxhp", player.maxhp);
        setting.setValue("Global reinforcement/cr_hp", player.hp);
        setting.setValue("Global reinforcement/cr_atk", player.atk);
        setting.setValue("Global reinforcement/cr_shotspeed", player.shotspeed);
        setting.setValue("Global reinforcement/cr_face", player.face);
        setting.setValue("Global reinforcement/cr_level", player.level);
        setting.setValue("Global reinforcement/cr_maxexp", player.maxexp);
        setting.setValue("Global reinforcement/cr_exp", player.exp);
        setting.setValue("Global reinforcement/cr_waepen", player.waepen);
        setting.setValue("Global reinforcement/cr_range", player.range);
        setting.setValue("Global reinforcement/cr_gold", player.gold);
        setting.setValue("Global reinforcement/cr_revive", player.revive);
        setting.sync();
    }
}

void gameScene::readdata(int x)
{
    if(x == 1)
    {
        QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
        if(setting.contains(tr("Global reinforcement/cr_maxhp")))
        {
            player.maxhp = setting.value("Global reinforcement/cr_maxhp").toInt();
            player.hp = setting.value("Global reinforcement/cr_hp").toInt();
            player.atk = setting.value("Global reinforcement/cr_atk").toInt();
            player.def = setting.value("Global reinforcement/cr_def").toInt();
            player.shotspeed = setting.value("Global reinforcement/cr_shotspeed").toInt();
            player.face = setting.value("Global reinforcement/cr_face").toInt();
            player.level = setting.value("Global reinforcement/cr_level").toInt();
            player.maxexp = setting.value("Global reinforcement/cr_maxexp").toInt();
            player.exp = setting.value("Global reinforcement/cr_exp").toInt();
            player.waepen =setting.value("Global reinforcement/cr_waepen").toInt();
            player.range = setting.value("Global reinforcement/cr_range").toInt();
            player.gold = setting.value("Global reinforcement/cr_gold").toInt();
            player.revive = setting.value("Global reinforcement/cr_revive").toInt();
        }
    }
    else
    {
        QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
        if(setting.contains(tr("Global reinforcement/used")))
        {
            player.maxhp = setting.value("Global reinforcement/maxhp").toInt();//将读取出的数据进行使用
            player.hp = setting.value("Global reinforcement/maxhp").toInt();
            player.atk = setting.value("Global reinforcement/atk").toInt();
            player.def = setting.value("Global reinforcement/def").toInt();
            player.shotspeed = setting.value("Global reinforcement/shotspeed").toInt();
            player.movespeed = setting.value("Global reinforcement/movespeed").toInt();
        }
    }
    updateLabel();
}

//更新状态面板
void gameScene::updateLabel()
{
    QString text;
    text.append("生命值\n");
    text.append(QString::number(player.hp));
    text.append("/");
    text.append(QString::number(player.maxhp));
    hpLabel->setText(text);
    hpLabel->setAlignment(Qt::AlignCenter);
    text.clear();

    text.append("等级\nLv");
    text.append(QString::number(player.level));
    text.append(":");
    text.append(QString::number(player.exp));
    text.append("/");
    text.append(QString::number(player.maxexp));
    levelLabel->setText(text);
    levelLabel->setAlignment(Qt::AlignCenter);
    text.clear();

    text.append("攻击力:");
    text.append(QString::number(player.atk));
    atkLabel->setText(text);
    atkLabel->setAlignment(Qt::AlignCenter);
    text.clear();

    text.append("防御力:");
    text.append(QString::number(player.def));
    defLabel->setText(text);
    defLabel->setAlignment(Qt::AlignCenter);
    text.clear();

    text.append("射速:");
    text.append(QString::number(player.shotspeed));
    stspdLabel->setText(text);
    stspdLabel->setAlignment(Qt::AlignCenter);
    text.clear();

    text.append("射程:");
    text.append(QString::number(player.range));
    rangeLabel->setText(text);
    rangeLabel->setAlignment(Qt::AlignCenter);
    text.clear();

    text.append("金币:");
    text.append(QString::number(player.gold));
    goldLabel->setText(text);
    goldLabel->setAlignment(Qt::AlignCenter);
    text.clear();

}
void gameScene::levelUp()
{
    int a = 0, b = 0 , c = 0;
    a = random(0,levelUpList.size() - 1 );
    b = random(0,levelUpList.size() - 1);
    c = random(0,levelUpList.size() - 1);
    while(a == b || a == c || b == c)
    {
        b = random(0,levelUpList.size() - 1);
        c = random(0,levelUpList.size() - 1);
    }
    if(isrunning)
    {
        gamepause();
        pausedBackgroundLabel->show();
        levelUpList[a]->show();
        levelUpList[b]->show();
        levelUpList[c]->show();
        levelUpList[a]->move(800,500);
        levelUpList[b]->move(900,500);
        levelUpList[c]->move(1000,500);
    }
    else
    {
        gamepause();
        pausedBackgroundLabel->hide();
        for(auto i : levelUpList)
        {
            i->hide();
        }
    }
    updateLabel();
}

//生成随机数
int gameScene::random(int begin, int limit)
{
    int x = begin + qrand() % (begin - limit);
//    qDebug() << x  << endl;
    return x ;
}

//距离计算
int gameScene::distance(int x, int y, int tx, int ty)
{
    int aim = (int)(sqrt( pow(x - tx , 2) + pow(y - ty , 2) ) );
    return aim;
}
//失败
void gameScene::dead()
{
    QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
    if(setting.contains(tr("Global reinforcement/used")))
    {
        int gold = setting.value("Global reinforcement/gold").toInt();
        setting.setValue("Global reinforcement/gold", player.gold + gold);
        setting.sync();
    }
    gamepause();


    gameoverLabel->show();
    button_back->show();
}
