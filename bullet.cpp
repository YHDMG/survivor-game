#include "bullet.h"

bullet::bullet(QObject *parent)
{

}

bullet::bullet(QPoint pos, QPixmap pix, int type, QPoint point, int range)
{
    this->setPos(pos);
    this->setPixmap(pix);
    this->mtype = type;
    this->point = point;
    this->life = range;
    this->damage = 20;
}

void bullet::bulletmove()
{
    this->moveBy(point.x() , point.y()  );
}
