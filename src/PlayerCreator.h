//
// Created by siwekm on 22.04.20.
//

#ifndef SEM_PLAYERCREATOR_H
#define SEM_PLAYERCREATOR_H
#include "Player.h"
#include <ncurses.h>


/** Allows to edit player attributes at the start of new game */
class PlayerCreator{
private:
    Player &m_player;
    /** Show attribute */
    void ShowAttribute(std::pair<std::string, int> att, int num, WINDOW *m_menu);
public:
    PlayerCreator(Player &player);
    /** Set player name*/
    void SetName();
    /** Display player creator*/
    void Show();
};

#endif //SEM_PLAYERCREATOR_H
