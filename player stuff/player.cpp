#include "xo/xo.h"
#include "xo/menuXo.h"
#include "connect 4/connect4.h"
#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
Player::Player()
{
    name = "";
    symbol = ' ';
    score = 0;
}
Player::Player(std::string name, char symbol)
{

    this->name = name;
    this->symbol = symbol;
    score = 0;
}
std::string Player::getName()
{
    return name;
}
char Player::getSymbol()
{
    return symbol;
}
int Player::getScore()
{
    return score;
}
void Player::incrementScore()
{
   this->score++;
}
void Player::setName(std::string name)
{
    this->name = name;
}
void Player::setSymbol(char symbol)
{
    this->symbol = symbol;
}
void Player::validateSymbol()
{
  while(getSymbol()!= 'X' && getSymbol()!= 'O')
  {
    std::cout<<"Invalid symbol. Please enter 'X' or 'O': ";
    char s;
    input(s);
    setSymbol(s);
  }     
}