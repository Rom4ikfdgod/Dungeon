#ifndef ENEMY_H
#define ENEMY_H
#include <cmath>
class Enemy
{
public:
Enemy();
~Enemy();
int koeff;
int hp;
int att;
int attack();
bool isAlive();
void get_damage(int att);
};

#endif // ENEMY_H
