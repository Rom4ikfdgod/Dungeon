#ifndef WIDGET_H
#define WIDGET_H
#include "enemy.h"
#include "player.h"
#include <QTimer>

#include <QWidget>
#include <QtGui>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    int fight = 0;
    int alert_on = 0;
    int fight_stage=0;

    int fight_player_x = 2;
    int fight_player_y = 7;
    int boss_x = 7;
    int boss_y = 4;
    int point_x=9;
    int point_y=6;
    int mobe_x = 9;
    int mobe_y = 7;
    int aaaa_x = 8;
    int aaaa_y = 3;

    int wblocks = 13;
    int hblocks = 13;

    int player_x = 6;
    int player_y = 6;

    int rooms =1;

public:
    int game_map[13][13];
    QTimer timer;
    QTimer timer_2;
    QTimer timer_3;

    explicit Widget(QWidget *parent = 0);
    ~Widget();
    Enemy * en;
    Player * player_1;
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *key);
    void Fight(QKeyEvent *k);
    void alert();
private:
    Ui::Widget *ui;
public slots:
    void HP_BAR();
    void def();
    void generator();
};

#endif // WIDGET_H
