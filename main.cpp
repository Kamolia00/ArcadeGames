#include"xo.h"
#include"connect4.h"
#include"valid_input.h"
#include<iostream>
using namespace std;
int main() {
    cout << "Welcome to the Arcade Games!" << endl;
    int choice;
        int games_xo=0,games_connect4=0;
    while (true){
        cout << "Please enter the name of Player 1: ";
        string name1;
        input(name1);
        cout << "Please enter the name of Player 2: ";
        string name2;
        input(name2);
        cout << "Hello " << name1 << " and " << name2 << "! Let's start playing!" << endl;
        cout<<name1<<" choose your symbol (X or O): ";
        char symbol;
        input(symbol);
        while(symbol != 'X' && symbol != 'O' && symbol != 'x' && symbol != 'o'){
            cout << "Invalid symbol. Please choose X or O: ";
            cin >> symbol;

        }
        Player p1(name1, symbol);
        Player p2;
        if(symbol == 'X'){
            p2.setSymbol('O');
        }
        else{
            p2.setSymbol('X');
        }
        p2.setName(name2);
        while(true){
            cout << "Choose a game to play:" << endl;
            cout << "1. Tic Tac Toe" << endl;
            cout << "2. Connect 4" << endl;
            cout << "3. Exit" << endl;
            if (games_xo+games_connect4>0) {
                cout<<"4 Start new game";
            }
            cin >> choice;
            if (cin.fail()) {
                input(choice);
            }
            if(choice == 1){
                XO game(p1, p2);
                game.playGame();
                games_xo++;
                cout<<"the score is "<<p1.getScore()<<' '<<p2.getScore()<<endl;
            }
            else if(choice == 2){
                connect4 game(p1, p2);
                game.play_game();
                games_connect4++;
                cout<<"the score is "<<p1.getName()<<" = "<<p1.getScore()<<' '<<p2.getName()<<" = "<<p2.getScore()<<endl;
            }
            else if(choice == 3){
                cout<<"after "<<games_xo<<" of xo and "<<games_connect4<<" of connect4"<<"\n";
                if(p1.getScore() > p2.getScore()){
                    cout << p1.getName() << " wins the arcade with a score of " << p1.getScore() << "!" << endl;
                    cout<<p2.getName()<<"'s is "<<p2.getScore()<<endl;
                }
                else if(p2.getScore() > p1.getScore()){
                    cout << p2.getName() << " wins the arcade with a score of " << p2.getScore() << "!" << endl;
                    cout<<p1.getName()<<"'s is "<<p1.getScore()<<endl;
                }
                else{
                    cout << "It's a tie! Both players have a score of " << p1.getScore() << "!" << endl;
                }
                cout << "Thanks for playing! Goodbye!" << endl;
                break;
            }
            else if(choice == 4 and games_xo+games_connect4>0) {
                games_connect4=0;
                games_xo=0;
                break;
            }
            else{
                cout << "Invalid choice. Please try again." << endl;
            }
        }
if (choice==3) {
    break;
}
    }
        return 0;
}