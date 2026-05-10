#include"player.h"
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
    score++;
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
    char symbol;
    std::cin>>symbol;
    setSymbol(symbol);
  }     
}

