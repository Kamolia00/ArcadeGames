#include "valid_input.h"
#include <limits>
void input(char &c){
    while(true){
        if(std::cin >> c){
            break;
        }
        else{
            std::cout << "Error: Not a character. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
void input(int &i){
     while(true) {
        if (std::cin >> i) {
            break;
        }else {
            // Input failed (user typed letters, etc.)
            std::cout << "Error: Not a number. Try again." << std::endl;

            // 1. Reset the error flags
            std::cin.clear();

            // 2. Skip everything in the buffer until the next newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
void input(std::string &s) {
    while(true){
        std::getline(std::cin, s);
        if(s.empty()){
            std::cout << "Invalid input. Please enter a non-empty string: ";
        } else {
            break;
        }
    }
}