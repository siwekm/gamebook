
#ifndef SEM_POTI_H
#define SEM_POTI_H


#include <string>
#include "Player.h"
#include "Item.h"


/** Potion class. Modifies player stats before combat. */
class Potion: public Item{
private:
    int m_heal, m_speed;
public:
    Potion();
    Potion(std::string name, int heal, int speed);

    void use(Player& player, int id);
    /** Get inventory message. */
    std::string GetMessage();
    /** Get string to use in save file. */
    std::string GetSaveString();
    /** Get potion heal effect. */
    int GetHeal() const;
    /** Get potion speed effect. */
    int GetSpeed() const;
    std::string GetName();
};

#endif //SEM_POTI_H