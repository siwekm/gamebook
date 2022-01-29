#include <iostream>
#include <ncurses.h>
#include "PlayerCreator.h"
#include "Game.h"


int main() {
    std::string file_name;
    std::cout<<"Select book file:"<<std::endl;
    std::cin>>file_name;
    try{
        Game gameBook(file_name);
        gameBook.DisplayMenu();
    }catch (const std::exception &exc){
        std::cout<<exc.what()<<std::endl;
        std::cout<<"Invalid book file:"<<std::endl;
        return 0;
    }
    
    endwin();
    return 0;
}
