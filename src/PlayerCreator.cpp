//
// Created by siwekm on 22.04.20.
//

#include "PlayerCreator.h"
#include <iostream>


PlayerCreator::PlayerCreator(Player &player) : m_player(player){}
void PlayerCreator::SetName(){
    std::string name_line;
    std::cout<<"Choose player name: "<<std::endl;
    std::cin>>name_line;
    m_player.SetName(name_line);
}
void PlayerCreator::Show() {
    int maxPoints = 8;
    int spentPoints = 0;
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax); //-get sreen size
    WINDOW *m_menu = newwin(yMax, xMax, 0, 0);
    wclear(m_menu);
    int key;
    keypad(m_menu, true); //enable arrows
    auto attributes = m_player.GetAttributes();
    int pos = 0;
    std::pair<std::string, int> att_selected;
    do{
        int i=0;
        wclear(m_menu);
        refresh();
        wrefresh(m_menu);
        mvwprintw(m_menu, 1 , 1, "Points left: %d", maxPoints-spentPoints);
        for(auto it = attributes.begin(); it != attributes.end(); it++){
            if(pos == i){
                att_selected = std::pair(it->first, it->second);
                wattron(m_menu, A_REVERSE);
            }
            ShowAttribute(std::pair(it->first, it->second), i, m_menu);
            wattroff(m_menu, A_REVERSE);
            i++;
        }
        refresh();
        wrefresh(m_menu);
        key = wgetch(m_menu);

        switch(key){
            case KEY_UP://up
                if(pos > 0)
                    pos--;
                break;
            case KEY_DOWN://down
                if((unsigned long)pos < attributes.size()-1)
                    pos++;
                break;
            case KEY_RIGHT:
                if(att_selected.second < 10 && spentPoints < maxPoints){
                    att_selected.second++;
                    spentPoints++;
                }
                break;
            case KEY_LEFT:
                if(att_selected.second > 0){
                    att_selected.second--;
                    spentPoints--;
                }
                break;
        }
        attributes[att_selected.first] = att_selected.second;
    }while(key != '\n');
    //set player attributes
    for(auto it = attributes.begin(); it != attributes.end(); it++){
        m_player.SetAttribute(std::pair(it->first, it->second));
    }
    endwin();
}
void PlayerCreator::ShowAttribute(std::pair<std::string, int> att, int num, WINDOW *m_menu){
    int max = 10;
    mvwprintw(m_menu, (num*3)+2 , 1, att.first.c_str());
    for (int i = 0; i < max; i++) {
        move((num*3)+3, i+1);
        if(att.second > i){
            addch('#');
        }else{
            addch('_');
        }
    }
}