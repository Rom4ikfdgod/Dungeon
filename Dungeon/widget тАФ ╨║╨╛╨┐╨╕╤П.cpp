#include "widget.h"
#include "ui_widget.h"
#include <QtGui>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setGeometry(this->x(), this->y(), 600,600);

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
               if(rnd<950) game_map[i][j]=0;
               else game_map[i][j]=3;
           }
       }
   }
    if (doors ==0) generator();
}


void Widget::paintEvent(QPaintEvent *e)
{
    QImage grass(":/files/images_and_text/flour.png");
    QImage block(":/files/images_and_text/fight_bg.png");
    QImage player(":/files/images_and_text/player.png");
    QImage door(":/files/images_and_text/door.png");
    QImage box(":/files/images_and_text/box.png");

    QPainter painter(this);

    int wsize = this->width()/wblocks;
    int hsize = this->height()/hblocks;

    for (int i=0; i<wblocks; i++)
        for (int j=0; j<hblocks; j++)
            if (game_map[i][j]==0)
                painter.drawImage(i*wsize, j*hsize, grass.scaled(wsize, hsize));
            else if(game_map[i][j]==2)
            {
                painter.drawImage(i*wsize, j*hsize, door.scaled(wsize, hsize));
            }
            else if(game_map[i][j]==3)
                painter.drawImage(i*wsize, j*hsize, box.scaled(wsize, hsize));
            else
                painter.drawImage(i*wsize, j*hsize, block.scaled(wsize, hsize));
    painter.drawImage(player_x*wsize, player_y*hsize, player.scaled(wsize, hsize));
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if (e->key()==Qt::Key_D)
    {
        if (game_map[player_y][player_x+1]!=1)
            player_x++;
    }
    if (e->key()==Qt::Key_A)
        {
        if (game_map[player_y][player_x-1]!=1)
            player_x--;
        }
    if (e->key()==Qt::Key_W)
    {
        if (game_map[player_y-1][player_x]!=1)
            player_y--;
    }
    if (e->key()==Qt::Key_S)
    {
        if (game_map[player_y+1][player_x]!=1)
            player_y++;
    }
    if(game_map[player_y][player_x]==2) {
        if (player_x==12)
        {
             player_x=1;
        }
        else if (player_x==0)
        {
             player_x=11;
        }
        else if (player_y==12)
        {
             player_y=1;
        }
        else if (player_y==0)
        {
             player_y=11;
        }
        generator();
    }
    this->repaint();
}
