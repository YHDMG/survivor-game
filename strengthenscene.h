#ifndef STRENGTHENSCENE_H
#define STRENGTHENSCENE_H

#include <QWidget>
#include <QLabel>
class strengthenscene : public QWidget
{
    Q_OBJECT
public:
    explicit strengthenscene(QWidget *parent = nullptr);
    QLabel* infoLabel;
    QLabel* titleLabel;
    QLabel* bloodLabel;
    QLabel* attackLabel;
    QLabel* defenseLabel;
    QLabel* goldgainLabel;
    QLabel* reviveLabel;
    QLabel* goldLabel;
signals:
    void back();
};

#endif // STRENGTHENSCENE_H
