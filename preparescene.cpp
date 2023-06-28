#include "preparescene.h"
#include "button.h"
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QSettings>
prepareScene::prepareScene(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1920,1080);//设置窗口分辨率
    this->setWindowTitle("神秘的幸存者");//设置窗口标题
    //this->setWindowIcon();设置应用图片 no picture now :(
    //角色 单发
    button* button_start_a = new button;
    button_start_a->setParent(this);
    button_start_a->setIMage(":/wpA.png",":/wpA.png",":/wpA.png");
    button_start_a->move(this->width() * 0.5 - button_start_a->width() * 0.5,500);
    button_start_a->show();

    game_scene = new gameScene;

    connect(button_start_a, &button::clicked, [=]()
    {
        QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
        if(setting.contains(tr("Global reinforcement/used")))
        {
            game_scene->player.maxhp = setting.value("Global reinforcement/maxhp").toInt();
            game_scene->player.hp = setting.value("Global reinforcement/maxhp").toInt();
            game_scene->player.atk = setting.value("Global reinforcement/atk").toInt();
            game_scene->player.def = setting.value("Global reinforcement/def").toInt();
            game_scene->player.shotspeed = setting.value("Global reinforcement/shotspeed").toInt();
            game_scene->player.goldgain = setting.value("Global reinforcement/goldgain").toInt();
            game_scene->player.revive =  setting.value("Global reinforcement/revive").toInt();
        }
        //点击动画
        button_start_a->zoom();
        //属性修正
        game_scene->player.maxhp *= 0.8;
        game_scene->player.hp *= 0.8;
        game_scene->player.atk += 10;
        game_scene->player.def -= 10;
        game_scene->player.shotspeed *= 0.5;
        game_scene->player.waepen = 0;
        game_scene->player.range += 200;
        //跳转到选择人物的界面
        QTimer::singleShot(200,[=]()
        {
            this->hide();
            game_scene->show();
            game_scene->startgame();
        });
    });

    //角色 散射
    button* button_start_b = new button;
    button_start_b->setParent(this);
    button_start_b->setIMage(":/wpB.png",":/wpB.png",":/wpB.png");
    button_start_b->move(this->width() * 0.5 - button_start_b->width() * 0.5,700);
    button_start_b->show();
    game_scene = new gameScene;
    connect(button_start_b, &button::clicked, [=]()
    {
        QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
        if(setting.contains(tr("Global reinforcement/used")))
        {
            game_scene->player.maxhp = setting.value("Global reinforcement/maxhp").toInt();
            game_scene->player.hp = setting.value("Global reinforcement/maxhp").toInt();
            game_scene->player.atk = setting.value("Global reinforcement/atk").toInt();
            game_scene->player.def = setting.value("Global reinforcement/def").toInt();
            game_scene->player.shotspeed = setting.value("Global reinforcement/shotspeed").toInt();
            game_scene->player.goldgain = setting.value("Global reinforcement/goldgain").toInt();
            game_scene->player.revive =  setting.value("Global reinforcement/revive").toInt();
        }
        //点击动画
        button_start_b->zoom();
        game_scene->player.maxhp *= 1.2;
        game_scene->player.hp *= 1.2;
        game_scene->player.atk -= 20;
        game_scene->player.def += 0;
        game_scene->player.shotspeed *= 1.5;
        game_scene->player.waepen = 1;
        game_scene->player.range -= 100;
        //跳转到选择人物的界面
        QTimer::singleShot(200,[=]()
        {
            this->hide();
            game_scene->show();
            game_scene->startgame();
        });
    });

    connect(game_scene,&gameScene::backtomain, [=]()
    {
        emit this->backtomain();
    });

}
