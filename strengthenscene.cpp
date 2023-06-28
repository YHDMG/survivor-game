#include "strengthenscene.h"
#include "button.h"
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QSettings>
#include <QLabel>
strengthenscene::strengthenscene(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1920,1080);//设置窗口分辨率
    this->setWindowTitle("神秘的幸存者");//设置窗口标题
    //this->setWindowIcon();设置应用图片 no picture now :(


    int* maxhp = new int;
    int* atk= new int;
    int* def= new int;
    int* shotspeed= new int;
    int* movespeed= new int;
    int* gold = new int;
    int* goldgain = new int;
    int* revive = new int;

    int* maxhp_r= new int;
    int* atk_r= new int;
    int* def_r= new int;
    int* goldgain_r = new int;
    int* revive_r = new int;

    QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
    if(setting.contains(tr("Global reinforcement/used")))
    {
        *maxhp = setting.value("Global reinforcement/maxhp").toInt();//读取数据
        *atk = setting.value("Global reinforcement/atk").toInt();
        *def = setting.value("Global reinforcement/def").toInt();
        *shotspeed = setting.value("Global reinforcement/shotspeed").toInt();
        *movespeed = setting.value("Global reinforcement/movespeed").toInt();
        *maxhp_r = setting.value("Global reinforcement/maxhp_r").toInt();
        *atk_r = setting.value("Global reinforcement/atk_r").toInt();
        *def_r = setting.value("Global reinforcement/def_r").toInt();
        *gold = setting.value("Global reinforcement/gold").toInt();
        *goldgain = setting.value("Global reinforcement/goldgain").toInt();
        *revive = setting.value("Global reinforcement/revive").toInt();
        *goldgain_r = setting.value("Global reinforcement/goldgain_r").toInt();
        *revive_r = setting.value("Global reinforcement/revive_r").toInt();
    }


    //计分板背景
       infoLabel=new QLabel(this);
       infoLabel->setPixmap(QPixmap(tr(":/backgroud_s.png")));
       infoLabel->setScaledContents(true);
       infoLabel->move(0,0);
       infoLabel->show();
       //设置字体
       QPalette palette;
       palette.setColor(QPalette::WindowText,Qt::black);
       QFont font;
       font.setPointSize(15);
       font.setBold(true);
       QFont titleFont;
       titleFont.setPointSize(34);
       titleFont.setBold(true);


//位置

    //大标题
    titleLabel=new QLabel(this);
    titleLabel->setFixedSize(640,120);
    titleLabel->move(650,150);
    titleLabel->setPalette(palette);
    titleLabel->setFont(titleFont);
    titleLabel->show();
    //生命值
    bloodLabel=new QLabel(this);
    bloodLabel->setFixedSize(60*2,80);
    bloodLabel->move(6*60,60*5);
    bloodLabel->setPalette(palette);
    bloodLabel->setFont(font);
    bloodLabel->show();
    //攻击力
    attackLabel=new QLabel(this);
    attackLabel->setFixedSize(60*2,80);
    attackLabel->move(6*60,60*7);
    attackLabel->setPalette(palette);
    attackLabel->setFont(font);
    attackLabel->show();
    //防御力
    defenseLabel=new QLabel(this);
    defenseLabel->setFixedSize(60*2,80);
    defenseLabel->move(6*60,60*9);
    defenseLabel->setPalette(palette);
    defenseLabel->setFont(font);
    //金币获取
    goldgainLabel=new QLabel(this);
    goldgainLabel->setFixedSize(60*2,80);
    goldgainLabel->move(6*60,60*11);
    goldgainLabel->setPalette(palette);
    goldgainLabel->setFont(font);
    //复活次数
    reviveLabel=new QLabel(this);
    reviveLabel->setFixedSize(60*2,80);
    reviveLabel->move(6*60,60*13);
    reviveLabel->setPalette(palette);
    reviveLabel->setFont(font);
    //金币
    goldLabel=new QLabel(this);
    goldLabel->setFixedSize(60*2,80);
    goldLabel->move(1200,60*5);
    goldLabel->setPalette(palette);
    goldLabel->setFont(font);


//数据

    QString text;
    text.append("强化商店\n");
    titleLabel->setText(text);
    titleLabel->setAlignment(Qt::AlignCenter);
    text.clear();

    //生命值
    text.append("生命值\n");
    text.append(QString::number(*maxhp));
    if(*maxhp_r <= 1000)
    {
        text.append("\n价格：");
        text.append(QString::number(*maxhp_r));
    }
    else
        text.append("\nMAX");
    bloodLabel->setText(text);
    bloodLabel->setAlignment(Qt::AlignCenter);
    text.clear();

    //攻击力
    text.append("攻击力\n");
    text.append(QString::number(*atk));
    if(*atk_r <= 1000)
    {
        text.append("\n价格：");
        text.append(QString::number(*atk_r));
    }
    else
        text.append("\nMAX");
    attackLabel->setText(text);
    attackLabel->setAlignment(Qt::AlignCenter);
    text.clear();

    //防御力
    text.append("防御力\n");
    text.append(QString::number(*def));
    if(*def_r <= 1000)
    {
        text.append("\n价格：");
        text.append(QString::number(*def_r));
    }
    else
        text.append("\nMAX");
    defenseLabel->setText(text);
    defenseLabel->setAlignment(Qt::AlignCenter);
    text.clear();
    //金币获取
    text.append("金币获取\n");
    text.append(QString::number(*goldgain));
    if(*goldgain_r <= 1000)
    {
        text.append("\n价格：");
        text.append(QString::number(*goldgain_r));
    }
    else
        text.append("\nMAX");
    goldgainLabel->setText(text);
    goldgainLabel->setAlignment(Qt::AlignCenter);
    text.clear();
    //复活次数
    text.append("复活次数\n");
    text.append(QString::number(*revive));
    if(*revive_r <= 1000)
    {
        text.append("\n价格：");
        text.append(QString::number(*revive_r));
    }
    else
        text.append("\nMAX");
    reviveLabel->setText(text);
    reviveLabel->setAlignment(Qt::AlignCenter);
    text.clear();

    //金币
    text.append("金币:");
    text.append(QString::number(*gold));
    goldLabel->setText(text);
    goldLabel->setAlignment(Qt::AlignCenter);
    text.clear();

    //返回
    button* button_back = new button;
    button_back->setParent(this);
    button_back->setIMage(":/back2.png",":/back2.png",":/back2.png");
    button_back->move(0,0);
    button_back->show();
    connect(button_back, &button::clicked, [=]()
    {
        this->hide();
        emit this->back();
    });

    button* button_maxhp = new button;
    button_maxhp->setParent(this);
    button_maxhp->setIMage(":/plus.png",":/plus.png",":/plus.png");
    button_maxhp->move(500 - button_maxhp->width() * 0.5,300);
    button_maxhp->show();
    connect(button_maxhp, &button::clicked, [=]()
    {
        if(*maxhp_r <= *gold)
        {
            if(*maxhp_r <= 1000)
            {
                *maxhp += 10;
                *gold -= *maxhp_r;
                *maxhp_r += 100;

                QString text;
                text.append("金币:");
                text.append(QString::number(*gold));
                goldLabel->setText(text);
                goldLabel->update();

                QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
                if(setting.contains(tr("Global reinforcement/used")))
                {
                    setting.setValue("Global reinforcement/maxhp", *maxhp);
                    setting.setValue("Global reinforcement/maxhp_r", *maxhp_r);
                    setting.setValue("Global reinforcement/gold", *gold);
                    setting.sync();
                }
                if(*maxhp_r == 1100)
                {
                    QString text;
                    text.append("生命值\n");
                    text.append(QString::number(*maxhp));
                    text.append("\nMAX");
                    bloodLabel->setText(text);
                    bloodLabel->update();
                }
                else
                {
                    QString text;
                    text.append("生命值\n");
                    text.append(QString::number(*maxhp));
                    text.append("\n价格：");
                    text.append(QString::number(*maxhp_r));
                    bloodLabel->setText(text);
                    bloodLabel->update();
                    button_maxhp->zoom();
                }
            }
       }
    });

    button* button_atk = new button;
    button_atk->setParent(this);
    button_atk->setIMage(":/plus.png",":/plus.png",":/plus.png");
    button_atk->move(500 - button_atk->width() * 0.5,420);
    button_atk->show();
    connect(button_atk, &button::clicked, [=]()
    {
        if(*atk_r <= *gold)
        {
            if(*atk_r <= 1000)
            {
                *atk += 1;
                *gold -= *atk_r;
                *atk_r += 100;

                QString text;
                text.append("金币:");
                text.append(QString::number(*gold));
                goldLabel->setText(text);
                goldLabel->update();

                QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
                if(setting.contains(tr("Global reinforcement/used")))
                {
                    setting.setValue("Global reinforcement/atk", *atk);
                    setting.setValue("Global reinforcement/atk_r", *atk_r);
                    setting.setValue("Global reinforcement/gold", *gold);
                    setting.sync();
                }
                if(*atk_r == 1100)
                {
                    QString text;
                    text.append("攻击力\n");
                    text.append(QString::number(*atk));
                    text.append("\nMAX");
                    attackLabel->setText(text);
                    attackLabel->update();
                }
                else
                {
                    QString text;
                    text.append("攻击力\n");
                    text.append(QString::number(*atk));
                    text.append("\n价格：");
                    text.append(QString::number(*atk_r));
                    attackLabel->setText(text);
                    attackLabel->update();
                    button_atk->zoom();
                }
            }
        }

    });


    button* button_def = new button;
    button_def->setParent(this);
    button_def->setIMage(":/plus.png",":/plus.png",":/plus.png");
    button_def->move(500 - button_def->width() * 0.5,540);
    button_def->show();
    connect(button_def, &button::clicked, [=]()
    {
        if(*def_r <= *gold)
        {
            if(*def_r <= 1000)
            {
                *def += 1;
                *gold -= *def_r;
                *def_r += 100;

                QString text;
                text.append("金币:");
                text.append(QString::number(*gold));
                goldLabel->setText(text);
                goldLabel->update();

                QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
                if(setting.contains(tr("Global reinforcement/used")))
                {
                    setting.setValue("Global reinforcement/def", *def);
                    setting.setValue("Global reinforcement/def_r", *def_r);
                    setting.setValue("Global reinforcement/gold", *gold);
                    setting.sync();
                }
                if(*def_r == 1100)
                {
                    QString text;
                    text.append("防御力\n");
                    text.append(QString::number(*def));
                    text.append("\nMAX");
                    defenseLabel->setText(text);
                    defenseLabel->update();
                }
                else
                {
                    QString text;
                    text.append("防御力\n");
                    text.append(QString::number(*def));
                    text.append("\n价格：");
                    text.append(QString::number(*def_r));
                    defenseLabel->setText(text);
                    defenseLabel->update();
                    button_def->zoom();
                }
            }
        }

    });

    button* button_goldgain = new button;
    button_goldgain->setParent(this);
    button_goldgain->setIMage(":/plus.png",":/plus.png",":/plus.png");
    button_goldgain->move(500 - button_goldgain->width() * 0.5,660);
    button_goldgain->show();
    connect(button_goldgain, &button::clicked, [=]()
    {
        if(*goldgain_r <= *gold)
        {
            if(*goldgain_r <= 1000)
            {
                *goldgain += 1;
                *gold -= *goldgain_r;
                *goldgain_r += 100;

                QString text;
                text.append("金币:");
                text.append(QString::number(*gold));
                goldLabel->setText(text);
                goldLabel->update();

                QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
                if(setting.contains(tr("Global reinforcement/used")))
                {
                    setting.setValue("Global reinforcement/goldgain", *goldgain);
                    setting.setValue("Global reinforcement/goldgain_r", *goldgain_r);
                    setting.setValue("Global reinforcement/gold", *gold);
                    setting.sync();
                }
                if(*goldgain_r == 1100)
                {
                    QString text;
                    text.append("金币获取\n");
                    text.append(QString::number(*goldgain));
                    text.append("\nMAX");
                    goldgainLabel->setText(text);
                    goldgainLabel->update();
                }
                else
                {
                    QString text;
                    text.append("金币获取\n");
                    text.append(QString::number(*goldgain));
                    text.append("\n价格：");
                    text.append(QString::number(*goldgain_r));
                    goldgainLabel->setText(text);
                    goldgainLabel->update();
                    button_goldgain->zoom();
                }
            }
        }

    });

    button* button_revive = new button;
    button_revive->setParent(this);
    button_revive->setIMage(":/plus.png",":/plus.png",":/plus.png");
    button_revive->move(500 - button_revive->width() * 0.5,780);
    button_revive->show();
    connect(button_revive, &button::clicked, [=]()
    {
        if(*revive_r <= *gold)
        {
            if(*revive_r <= 1000)
            {
                *revive += 1;
                *gold -= *revive_r;
                *revive_r += 100;

                QString text;
                text.append("金币:");
                text.append(QString::number(*gold));
                goldLabel->setText(text);
                goldLabel->update();

                QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
                if(setting.contains(tr("Global reinforcement/used")))
                {
                    setting.setValue("Global reinforcement/revive", *revive);
                    setting.setValue("Global reinforcement/revive_r", *revive_r);
                    setting.setValue("Global reinforcement/gold", *gold);
                    setting.sync();
                }
                if(*def_r == 1100)
                {
                    QString text;
                    text.append("复活次数\n");
                    text.append(QString::number(*revive));
                    text.append("\nMAX");
                    reviveLabel->setText(text);
                    reviveLabel->update();
                }
                else
                {
                    QString text;
                    text.append("复活次数\n");
                    text.append(QString::number(*revive));
                    text.append("\n价格：");
                    text.append(QString::number(*revive_r));
                    reviveLabel->setText(text);
                    reviveLabel->update();
                    button_revive->zoom();
                }
            }
        }

    });

}

