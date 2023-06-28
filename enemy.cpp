#include "enemy.h"

enemy::enemy(QObject *parent) : QObject(parent)
{

}

enemy::enemy(QPoint pos, QPixmap pix, int type)
{
    maxhp = 100;
    hp = 100;
    atk = 10;
    def = 10;
    this->type = type;
    this->setPos(pos);
    this->setPixmap(pix);
    this->pix = pix;
    movepicture = 0;

}
