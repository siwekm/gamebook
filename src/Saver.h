
//
// Created by siwekm
//

#ifndef SEM_SAVER_H
#define SEM_SAVER_H

#include <string>
#include <fstream>
#include <iostream>
#include "Player.h"
#include "Item.h"
#include "Weapon.h"
#include "Potion.h"

class Saver{
public:
    void Save(Player player, std::string saveFile);
    void Load(Player& player, std::string saveFile);
};


#endif //SEM_SAVER_H