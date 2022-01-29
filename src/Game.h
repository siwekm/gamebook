//
// Created by siwekm on 10.05.20.
//

#ifndef SEM_GAME_H
#define SEM_GAME_H

#include <iostream>
#include "World.h"
#include "Player.h"
#include "Weapon.h"
#include "Potion.h"

/** Main game class. User input controll. Game interface.
*/
class Game {
public:
    Game(std::string file_name);
    Game() = delete;
    /** Setup player and his stats */
    void SetupPlayer();
    /** Main game loop*/
    void Play();
    /** Display end game message */
    void Death();
    /** Display menu options */
    void DisplayMenu();
private:
    World gameWorld;
    Player gamePlayer;
    int maxHealth = 10;
    int maxInvSize = 10;

    /** Display game tutorial */
    void DisplayTutorial();
    /** Display player inventory */
    void DisplayPlayerInventory();
    /** Display generic message */
    void DisplayMessage(std::string msg);
    /** Display player stats */
    void DisplayPlayerStats();
    /** Display location and its options */
    int DisplayLocation(Location tmp);
    /** Display found weapon stats */
    void DisplayWeapon(Weapon wpn);
};

#endif //SEM_GAME_H
