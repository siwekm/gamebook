//
// Created by siwekm on 22.04.20.
//

#ifndef SEM_PLAYER_H
#define SEM_PLAYER_H

#include "Entity.h"
#include "Inventory.h"


/** Player class. Controlled by user. */
class Player : public Entity{
private:
    int current_location;
    int m_damage_bonus = 0;
public:
    Inventory inv;
    Player(){}
    Player(std::string name);
    /** Set player name */
    void SetName(std::string name);
    /** Set player health */
    void SetHealth(int health);
    /** Set player current location id */
    void SetLocation(int loc);
    /** Get player current location id */
    int GetLocationId() const;
    /** Get attack damage */
    int Attack();
    /** Fight entity */
    bool Fight(Entity target);
    /** *Try to run away from enemy.
     * @return true if succesful */
    bool RunAway(Entity enemy);
    /** Save Player data to save */
    void Save(std::string saveFile);
    /** Load Player data from save */
    void Load(std::string saveFile);
    /** Set damage bonus*/
    void SetDamgeBonus(int dmg);
    /** Get damage bonus*/
    int GetDamageBonus() const;
};


#endif //SEM_PLAYER_H
