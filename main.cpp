#include "xo.h"
#include "connect4.h"
#include "valid_input.h"
#include "player.h"
#include <iostream>

using namespace std;

int main()
{
    while(true)
    {
        int main_choice;

        cout << "\n===== GAME HUB =====\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs AI\n";
        cout << "3. Exit\n";

        input(main_choice);

        while(main_choice < 1 || main_choice > 3)
        {
            cout << "Invalid choice. Try again: ";
            input(main_choice);
        }

        // ================= PvP =================
        // ================= PvP =================
if(main_choice == 1)
{
    int games_xo = 0;
    int games_connect4 = 0;

    bool back_to_main = false;

    while(true)
    {
        cin.ignore();
//=======
// player info
      Player p1,p2;
        string player_name1,player_name2;
        cout << "Player 1 Enter your name: ";
        input(player_name1);
        p1.setName(player_name1);
        cout<<"Player 2 Enter your name: ";
        input(player_name2);
        p2.setName(player_name2);
        cout<<p1.getName()<<" Choose 'X' or 'O': ";
        char symbol;
        input(symbol);
        p1.setSymbol(symbol);
        p1.validateSymbol();
        if (p1.getSymbol()=='X')
       p2.setSymbol('O');
        else
            p2.setSymbol('X');
        cout<<p1.getName()<<" Your symbol is"<<p1.getSymbol()<<'\n';
        cout<<p2.getName()<<" Your symbol is "<<p2.getSymbol()<<'\n';
        // game is on
        while(true)
        {
            int choice;

            cout << "\n===== PvP MENU =====\n";
            cout << "1. Tic Tac Toe\n";
            cout << "2. Connect 4\n";
            cout << "3. Main Menu\n";

            if(games_xo + games_connect4 > 0)
            {
                cout << "4. New Players\n";
            }

            input(choice);

            if(choice == 1)
            {
                XO game(p1, p2);

                game.playGame();

                games_xo++;

                cout << "\nScore:\n";

                cout << p1.getName()
                     << " = "
                     << p1.getScore()
                     << endl;

                cout << p2.getName()
                     << " = "
                     << p2.getScore()
                     << endl;
            }

            else if(choice == 2)
            {
                connect4 game(p1, p2);

                game.play_game();

                games_connect4++;

                cout << "\nScore:\n";

                cout << p1.getName()
                     << " = "
                     << p1.getScore()
                     << endl;

                cout << p2.getName()
                     << " = "
                     << p2.getScore()
                     << endl;
            }

            else if(choice == 3)
            {
                back_to_main = true;
                break;
            }

            else if(choice == 4 &&
                    games_xo + games_connect4 > 0)
            {
                break;
            }

            else
            {
                cout << "Invalid choice.\n";
            }
        }

        if(back_to_main)
        {
            break;
        }
    }
}
        // ================= AI =================
        else if(main_choice == 2)
        {
            while(true)
            {
                cin.ignore();

                string player_name;

                cout << "Enter your name: ";
                input(player_name);

                char symbol;

                cout << "Choose X or O: ";
                input(symbol);

                while(symbol != 'X' && symbol != 'O' &&
                      symbol != 'x' && symbol != 'o')
                {
                    cout << "Invalid symbol. Choose X or O: ";
                    input(symbol);
                }

                if(symbol == 'x') symbol = 'X';
                if(symbol == 'o') symbol = 'O';

                Player human(player_name, symbol);

                Player ai;

                ai.setName("AI");

                if(symbol == 'X')
                    ai.setSymbol('O');
                else
                    ai.setSymbol('X');

                int difficulty;

                cout << "\nChoose Difficulty\n";
                cout << "1. Easy\n";
                cout << "2. Hard\n";

                input(difficulty);

                while(difficulty < 1 || difficulty > 2)
                {
                    cout << "Invalid difficulty: ";
                    input(difficulty);
                }

                while(true)
                {
                    XO game(human, ai);

                    if(difficulty == 1)
                    {
                        game.vsai_easy();
                    }
                    else
                    {
                        game.vsai_hard();
                    }

                    cout << "\nScore:\n";
                    cout << human.getName() << " = "
                         << human.getScore() << endl;

                    cout << ai.getName() << " = "
                         << ai.getScore() << endl;

                    int after;

                    cout << "\n1. Play Again\n";
                    cout << "2. New Player\n";
                    cout << "3. Main Menu\n";

                    input(after);

                    while(after < 1 || after > 3)
                    {
                        cout << "Invalid choice: ";
                        input(after);
                    }

                    if(after == 1)
                    {
                        continue;
                    }

                    else if(after == 2)
                    {
                        break;
                    }

                    else
                    {
                        goto MAIN_MENU;
                    }
                }
            }
        }

        // ================= EXIT =================
        else
        {
            cout << "Thanks for playing!\n";
            break;
        }

        MAIN_MENU:;
    }

    return 0;
}