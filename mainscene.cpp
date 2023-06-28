#include "mainscene.h"
#include "ui_mainscene.h"
#include "button.h"
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QSettings>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);


    QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
    if(!setting.contains(tr("Global reinforcement/used")))//如果已经存在这个文件，那就进行读取
    {
        setting.beginGroup(tr("Global reinforcement"));//节点开始
        setting.setValue("used","1");
        setting.setValue("maxhp","100");//设置key和value，也就是参数和值
        setting.setValue("atk","50");
        setting.setValue("def","10");
        setting.setValue("maxhp_r","100");
        setting.setValue("atk_r","100");
        setting.setValue("def_r","100");
        setting.setValue("shotspeed","500");
        setting.setValue("movespeed","2");
        setting.setValue("gold","0");
        setting.setValue("goldgain","1");
        setting.setValue("revive","0");
        setting.setValue("goldgain_r","100");
        setting.setValue("revive_r","100");
        setting.setValue("gold","0");
        setting.setValue("cr_maxhp", "100");
        setting.setValue("cr_hp", "100");
        setting.setValue("cr_atk", "50");
        setting.setValue("cr_shotspeed", "500");
        setting.setValue("cr_face", "1");
        setting.setValue("cr_level", "0");
        setting.setValue("cr_maxexp", "100");
        setting.setValue("cr_exp", "0");
        setting.setValue("cr_waepen", "1");
        setting.setValue("cr_range", "500");
        setting.setValue("cr_gold", "0");
        setting.setValue("cr_revive","0");
        setting.endGroup();//节点结束
    }



    this->setFixedSize(1920,1080);//设置窗口分辨率
    this->setWindowTitle("神秘的幸存者");//设置窗口标题
    //this->setWindowIcon();设置应用图片 no picture now :(

    prepare_scene = new prepareScene;
    connect(prepare_scene, &prepareScene::backtomain, [=]()
    {
        prepare_scene->game_scene->close();
        this->show();
    });


    //开始按钮
    button* button_start = new button;
    button_start->setParent(this);
    button_start->setIMage(":/start.png",":/start.png",":/start.png");
    button_start->move(this->width() * 0.5 - button_start->width() * 0.5,200);
    button_start->show();
    connect(button_start, &button::clicked, [=]()
    {
        //点击动画
        button_start->zoom();
        //跳转到选择人物的界面
        QTimer::singleShot(200,[=]()
        {
            this->hide();
            prepare_scene->show();
        });
    });

    //退出按钮

    button* button_exit = new button;
    button_exit->setParent(this);
    button_exit->setIMage(":/exit.png",":/exit.png",":/exit.png");
    button_exit->move(this->width() * 0.5 - button_exit->width() * 0.5,800);
    button_exit->show();
    connect(button_exit,&button::clicked,[=]()
    {
        button_exit->zoom();
        this->close();
    });
    //游玩教程按钮
    //to do ......

    //强化按钮
    strength_scene = new strengthenscene;
    connect(strength_scene, &strengthenscene::back, [=]()
    {
        this->show();
    });
    button* button_strengthen = new button;
    button_strengthen->setParent(this);
    button_strengthen->setIMage(":/shop.png",":/shop.png",":/shop.png");
    button_strengthen->move(this->width() * 0.5 - button_exit->width() * 0.5,600);
    button_strengthen->show();
    connect(button_strengthen, &button::clicked, [=]()
    {
        //点击动画
        button_strengthen->zoom();
        //跳转到选择人物的界面
        QTimer::singleShot(200,[=]()
        {
            this->hide();
            strength_scene->show();
        });
    });

    //继续游戏
    button* button_continue = new button;
    button_continue->setParent(this);
    button_continue->setIMage(":/continue.png",":/continue.png",":/continue.png");
    button_continue->move(this->width() * 0.5 - button_continue->width() * 0.5,400);
    button_continue->show();
    connect(button_continue, &button::clicked, [=]()
    {
        QSettings setting("D:/QT/qt_code/Survivor_beta/i.ini",QSettings::IniFormat);
        button_continue->zoom();
        //跳转到选择人物的界面
        QTimer::singleShot(200,[=]()
        {
            this->hide();
            prepare_scene->game_scene->show();
            prepare_scene->game_scene->readdata(1);
            prepare_scene->game_scene->startgame();
        });
    });

}

void MainScene::paintEvent(QPaintEvent *)
{
    //主界面背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/");// no picture now
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //主界面标题
    pix.load(":/");
    pix = pix.scaled(pix.width() * 1.0, pix.height() * 1.0);
    painter.drawPixmap(960, 200, pix);

}

MainScene::~MainScene()
{
    delete ui;
}

