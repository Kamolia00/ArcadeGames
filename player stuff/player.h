#ifndef player_h
#define player_h
#include "xo/xo.h"
#include "xo/menuXo.h"
#include "connect 4/connect4.h"
#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
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