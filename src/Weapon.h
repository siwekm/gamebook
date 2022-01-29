//
// Created by siwekm on 27.05.20.
//

#ifndef SEM_WEAP_H
#define SEM_WEAP_H


#include <string>
#include "Item.h"
#include "Player.h"


/** Weapon class. Modifies player damage in combat. */
class Weapon: public Item{
private:
    int m_damage;
public:
    Weapon();
    Weapon(std::string name, int damage);

    void use(Player& player, int id);
    std::string GetMessage();
    std::string GetSaveString();
    /** Get weapon damage. */
    int GetDamage();
};


#endif //SEM_WEAP_H