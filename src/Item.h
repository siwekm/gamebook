//
// Created by siwekm on 27.05.20.
//

#ifndef SEM_ITEM_H
#define SEM_ITEM_H


#include <string>
#include "Player.h"


/** Basic item. */
class Item {
protected:
    std::string m_name;
public:
    //Item();
    virtual ~Item() = default;
    virtual void use(Player& player, int id) = 0;
    virtual std::string GetMessage() = 0;
    virtual std::string GetSaveString() = 0;
    /** Set item name. */
    void SetName(std::string name);
    /** Get item name. */
    std::string GetName() const;
};


#endif //SEM_ITEM_H
