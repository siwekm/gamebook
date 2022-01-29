//
// Created by siwekm on 30.04.20.
//

#ifndef SEM_LOCATION_H
#define SEM_LOCATION_H


#include <set>
#include "Entity.h"
#include "Item.h"
#include "Weapon.h"
#include "Potion.h"

/** Stores location optin data. */
class Option {
private:
    std::string m_action;
    int m_next_success, m_next_fail;
    std::string m_text_success, m_text_fail;
public:
    Option(std::string action, int next_success, int next_fail, std::string text_success, std::string text_fail);
    /** Get id where option is pointing.
     */
    int GetNextSuccess() const;
    int GetNextFail() const;
    /** Get name of action.
     */
    std::string GetAction() const;
    /** Get success text.
     */
    std::string GetTextSuccess() const;
    std::string GetTextFail() const;
};
/** Stores all location data. */
class Location {
private:
    int m_id;
    std::string m_name;
    std::string m_description;
    std::vector<Option> options;
    Potion m_potionDrop;
    Weapon m_weaponDrop;
public:
    Entity m_enemy;
    Location(int id, std::string &name,  std::string &desc, Entity &enemy);
    /** Add interaction option to location. */
    void addOption(Option opt);
    /** Get location id. */
    int getId() const;
    /** Get set of all location ids where option are pointing. */
    std::set<int> GetOptionsIds() const;
    /** Get vector of all option. */
    std::vector<Option> GetOptions() const;
    /** Get location name */
    std::string GetName() const;
    /** Get description of location. */
    std::string GetDescription() const;
    /** True if location enemy health > 0 */
    bool HasEnemy() const;
    /** Set location weapon drop. */
    void SetWeapon(Weapon x);
    /** Set location potion drop.*/
    void SetPotion(Potion x);
    /** Get weapon drop*/
    Weapon* GetWeapon();
    /** Get potion drop */
    Potion* GetPotion();
};


#endif //SEM_LOCATION_H
