#ifndef player_h
#define player_h
#include<iostream>
#include<string>
class Player
{  
    private:
    std::string name;
    char symbol;
    int score;
    public:
    Player();
    Player(std::string name, char symbol);
    std::string getName();
    char getSymbol();
    int getScore();
    void incrementScore();
    void setName(std::string name);
    void setSymbol(char symbol);
    void validateSymbol();
 };
#endif 