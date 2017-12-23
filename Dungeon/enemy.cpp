#include "enemy.h"

Enemy::Enemy()
{
att=10;//+k*2;
hp=100;//*k;
}

int Enemy::attack()
{
return this->att;
}

bool Enemy::isAlive()
{
if (this->hp<=0)
return true;
else
return false;
}

void Enemy::get_damage(int attack)
{
this->hp-=attack;
}
