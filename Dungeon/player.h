#ifndef PLAYER_H
#define PLAYER_H
#include <QKeyEvent>
#include "enemy.h"
class Player : public Enemy
{
public:
    Player();
    ~Player();
    int attack;
    bool defense=false;
    bool defensed();
    void increase_damage();
    void increase_HP();
};

#endif // PLAYER_H
