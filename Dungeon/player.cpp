#include "player.h"

Player::Player():Enemy()
{
att=5;//+k;//*2;
hp=100;//+k;//*5;
}

bool Player::defensed()
{
if (defense)
this->defense=false;
else
this->defense=true;
}

void Player::increase_damage()
{
this->att+=5;
}

void Player::increase_HP()
{
this->hp+=10;
}
