#include "loot.h"

loot::loot(QWidget *parent)
{

}

loot::loot(QPoint pos, QPixmap pix, int type)
{
    this->setPos(pos);
    this->setPixmap(pix);
    this->type = type ;
}
