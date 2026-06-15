#ifndef player_h
#define player_h
#include "player stuff/valid_input.h"
#include <string>
#include <iostream>
class Player
{  
    private:
    std::string name;
    char symbol;
    int score;
    public:
    Player();
    Player(std::string name, char symbol);
    std::string getName() const;
    char getSymbol() const;
    int getScore() const;
    void incrementScore();
    void setName(std::string name);
    void setSymbol(char symbol);
    void validateSymbol();
    void setScore(int s);
    void addScore(int points);
 };
#endif 