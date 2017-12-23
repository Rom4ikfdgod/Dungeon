/*Сделать функцию Alert с таймером_3 для отрисовки предупреждения
Сделать функцию Fight_paint для дебага отрисовки моба
Добавить хилку +10 к хп(сделано)
Пофиксить постоянную перерисовку мобов(сделано, надо было repaint передвинуть)
Сделать игру заканчиваемой
Добавить счетчик коробок ибо их мало
Фикс Lcd на Att
Переработать боевку
Проработать ProgressBar - для HP
*/



#include "widget.h"
#include "ui_widget.h"
#include <QtGui>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QString>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    player_1=new Player;
    en = new Enemy();
    connect(&timer,SIGNAL(timeout()),this,SLOT(def()));
    connect(&timer_2,SIGNAL(timeout()),this,SLOT(HP_BAR()));
    ui->lcdNumber->hide();
    ui->lcdNumber_2->hide();
    ui->lcdNumber_3->hide();
    ui->lcdNumber_4->hide();

    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();

    generator();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::generator()
{
    int doors = 0;
    for (int i=0;i<13;i++)
   {
       for(int j=0;j<13;j++)
       {

           int rnd= rand()%1000;
           if(i==0 or i==12 or j==0 or j==12)
           {
               if((i==j)or(i==0 and j ==12)or(i==12 and j==0)) game_map[i][j] = 1;
               else if(rnd<(900)) game_map[i][j]=1;
               else
               {
                   game_map[i][j] = 2;
                   doors++;
               }
           }
           else
           {
              if(rnd<970) game_map[i][j]=0;
              else if (rnd>980){
                   if(((game_map[i+1][j]) and (game_map[i-1][j]) and (game_map[i][j+1]) and (game_map[i][j-1]))!=3)
                   {
                       game_map[i][j] = 3;
                   }
                   else
                       game_map[i][j] = 0;
               }
              else
              {
                   if(((game_map[i+1][j]) and (game_map[i-1][j]) and (game_map[i][j+1]) and (game_map[i][j-1])) != 4)
                   {
                       game_map[i][j] = 4;
                   }
                   else
                       game_map[i][j] = 0;
              }
           }
       }
   }
    if (doors ==0) generator();
}

void Widget::def()
{
    if (!(player_1->defense))
        player_1->get_damage(en->att);
    ui->lcdNumber_3->display(player_1->hp);
    ui->lcdNumber->display(player_1->attack);
    ui->lcdNumber_4->display(en->hp);
    ui->lcdNumber_2->display(en->att);

    player_1->defense=false;
}

void Widget::HP_BAR()
{
    if (en->isAlive())
    {
        fight=0;
        this->repaint();
    }
    else if (player_1->isAlive())
    {
        this->close();
    }

    ui->lcdNumber->display(player_1->hp);
    ui->lcdNumber_3->display(player_1->attack);
    ui->lcdNumber_2->display(en->hp);
    ui->lcdNumber_4->display(en->att);
}

void Widget::Fight(QKeyEvent *k)
{
    if (fight!=0)
    {
        switch (fight_stage)
        {
            case 0:
        {
                if (k->key()==Qt::Key_E)
                {

                }



        }
            break;

            case 1:
        {



        }

            break;
        }


    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QImage grass(":/files/images_and_text/flour.png");
    QImage block(":/files/images_and_text/fight_bg.png");
    QImage player(":/files/images_and_text/player.png");
    QImage door(":/files/images_and_text/door.png");
    QImage box(":/files/images_and_text/box.png");
    QImage aaa(":/files/images_and_text/ext_point.png");
    QImage heart(":/files/images_and_text/Heart.png");
    int wsize = this->width()/wblocks;
    int hsize = this->height()/hblocks;
    int w = this->width();
    int h = this->height();
    QPainter painter(this);

    ui->lcdNumber->setGeometry(w*0.15, h*0.7, w * 0.1, h * 0.1);
    ui->lcdNumber_3->setGeometry(w*0.15, h*0.1, w * 0.1, h * 0.1);

    ui->lcdNumber_2->setGeometry(w*0.68, h*0.7, w * 0.1, h * 0.1);
    ui->lcdNumber_4->setGeometry(w*0.68, h*0.1, w * 0.1, h * 0.1);

    ui->label->setGeometry(w*0.1, h*0.1, w * 0.1, h * 0.1);
    ui->label_2->setGeometry(w*0.63, h*0.1, w * 0.1, h * 0.1);

    ui->label_3->setGeometry(w*0.1, h*0.7, w * 0.1, h * 0.1);
    ui->label_4->setGeometry(w*0.63, h*0.7, w * 0.1, h * 0.1);

    ui->lcdNumber->display(player_1->hp);
    ui->lcdNumber_3->display(player_1->attack);
    ui->lcdNumber_2->display(en->hp);
    ui->lcdNumber_4->display(en->att);

    ui->lcdNumber->show();
    ui->lcdNumber_2->show();
    ui->lcdNumber_3->show();
    ui->lcdNumber_4->show();

    ui->label->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();

    switch(fight)
    {
        case 0:
    {
            timer.stop();
            ui->lcdNumber->setGeometry(w*0.05, h*0.915, w * 0.1, h * 0.06);

            ui->lcdNumber->display(player_1->hp);

            ui->lcdNumber->show();

            ui->label->hide();
            ui->label_2->hide();
            ui->label_3->hide();
            ui->label_4->hide();

            ui->lcdNumber_2->hide();
            ui->lcdNumber_3->hide();
            ui->lcdNumber_4->hide();
            en=new Enemy;

            box = box.convertToFormat(QImage::Format_ARGB32_Premultiplied);
            for (int i=0; i<wblocks; i++)
                for (int j=0; j<hblocks; j++)
                    if (game_map[i][j]==0)
                        painter.drawImage(i*wsize, j*hsize, grass.scaled(wsize, hsize));
                    else if(game_map[i][j]==2)
                    {
                        painter.drawImage(i*wsize, j*hsize, door.scaled(wsize, hsize));
                    }
                    else if(game_map[i][j]==3)
                    {
                        painter.drawImage(i*wsize, j*hsize, grass.scaled(wsize, hsize));
                        painter.drawImage(i*wsize, j*hsize, box.scaled(wsize, hsize));
                    }
                    else if (game_map[i][j]==1)
                    {
                        painter.drawImage(i*wsize, j*hsize, block.scaled(wsize, hsize));
                    }
                    else if (game_map[i][j]==4)
                    {
                        painter.drawImage(i*wsize, j*hsize, grass.scaled(wsize, hsize));
                        painter.drawImage(i*wsize, j*hsize, heart.scaled(wsize, hsize));
                    }
            painter.drawImage(player_x*wsize, player_y*hsize, player.scaled(wsize, hsize));
            break;
    }
    case 1:
    {
        timer.start(1000);
        timer_2.start(1);

        if (alert_on==0)
        {
            painter.drawImage(point_x*wsize, point_y*hsize, grass.scaled(wsize, hsize));
            alert_on=!alert_on;
        }
        else
        {
            painter.drawImage(point_x*wsize, point_y*hsize, aaa.scaled(wsize, hsize));
            alert_on=!alert_on;
        }
        int randomizer=rand()%6;
        QImage mobe(":/files/images_and_text/mobe"+QString::number(randomizer)+".png");

        for (int i=0; i<wblocks; i++)
            for (int j=0; j<hblocks; j++)
                painter.drawImage(i*wsize, j*hsize, block.scaled(wsize, hsize));
        painter.drawImage(fight_player_x*wsize, fight_player_y*hsize, player.scaled(wsize, hsize));
        painter.drawImage(mobe_x*wsize, mobe_y*hsize, mobe.scaled(wsize, hsize));
        break;
    }

        case 2:
    {
        timer.start(1000);
        timer_2.start(1);

        ui->lcdNumber->show();
        ui->lcdNumber_2->show();

        int randzer=rand()%3;
        QImage boss(":/files/images_and_text/boss"+QString::number(randzer)+".png");

            for (int i=0; i<wblocks; i++)
                for (int j=0; j<hblocks; j++)
                    painter.drawImage(i*wsize, j*hsize, block.scaled(wsize, hsize));
            painter.drawImage(fight_player_x*wsize, fight_player_y*hsize, player.scaled(wsize, hsize));
            painter.drawImage(boss_x*wsize, boss_y*hsize, boss.scaled(wsize*4, hsize*4));

            break;
        }
    }
}

void Widget::keyPressEvent(QKeyEvent *key)
{
    if(fight==0)
    {
        if (key->key()==Qt::Key_D)
            if (game_map[player_x+1][player_y]!=1)
                player_x++;
        if (key->key()==Qt::Key_A)
            if (game_map[player_x-1][player_y]!=1)
                player_x--;
        if (key->key()==Qt::Key_W)
            if (game_map[player_x][player_y-1]!=1)
                player_y--;
        if (key->key()==Qt::Key_S)
            if (game_map[player_x][player_y+1]!=1)
                player_y++;

        if (game_map[player_x][player_y]==3){
            game_map[player_x][player_y]=0;
            if  (int i = rand()%100<=80){
                fight=1;
            }
            else
            {
                fight=2;
            }
            player_1->increase_damage();
            ui->lcdNumber->display(player_1->hp);
        }

        if (game_map[player_x][player_y]==4)
        {
            player_1->increase_HP();
            game_map[player_x][player_y]=0;
        }

        if(game_map[player_x][player_y]==2) {
            if (player_x==12)
            {
                 player_x=1;
            }
             if (player_x==0)
            {
                 player_x=11;
            }
             if (player_y==12)
            {
                 player_y=1;
            }
             if (player_y==0)
            {
                 player_y=11;
            }
             rooms++;
            if (rooms%10==0){
                 en=new Enemy;
                 fight = 2;
             }
            generator();
            }
        this->repaint();
        }

        else if(fight==1 or fight==2)
        {
            if (key->key()==Qt::Key_Space)
            {
               player_1->defensed();
            }
            if (key->key()==Qt::Key_E)
            {
                en->get_damage(player_1->att);
            }
        }
}
