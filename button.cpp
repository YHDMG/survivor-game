#include "button.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QRect>
button::button(QWidget *parent) : QWidget(parent)
{

}

void button::setIMage(QString normal, QString hover, QString pressed)
{
    //加载图片
    m_normal.load(normal);
    m_hover.load(hover);
    m_press.load(pressed);
    m_current = m_normal;

    //设置按钮大小
    setFixedSize(m_normal.size());
}

void button::mousePressEvent(QMouseEvent *event)
{
    //按下鼠标
    emit clicked();
    m_current = m_press;
    update();
}

void button::mouseReleaseEvent(QMouseEvent *event)
{
    //松开鼠标
    m_current = m_normal;
    update();
}

void button::enterEvent(QEvent *event)
{
    //鼠标进入
    m_current = m_hover;
    update();
}

void button::leaveEvent(QEvent *event)
{
    //鼠标离开
    m_current = m_normal;
    update();
}

void button::paintEvent(QPaintEvent *event)
{
    //绘图
    QPainter p(this);
    p.drawPixmap(rect(),m_current);
}

void button::zoom()
{
    // 点击动画
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x() + 5, this->y() + 5, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start();
}
