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
std::string Player::getName() const
{
    return name;
}
char Player::getSymbol() const
{
    return symbol;
}
int Player::getScore() const
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