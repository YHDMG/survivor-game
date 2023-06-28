#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>

class button : public QWidget
{
    Q_OBJECT
public:
    explicit button(QWidget *parent = nullptr);
    void setIMage(QString normal, QString hover, QString pressed);

    //点击动画
    void zoom();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
    void paintEvent(QPaintEvent* event);

signals:
    void clicked();

private:
    QPixmap m_normal;
    QPixmap m_press;
    QPixmap m_hover;
    QPixmap m_current;

};

#endif // BUTTON_H
