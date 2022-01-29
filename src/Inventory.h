//
// Created by siwekm on 27.05.20.
//

#ifndef SEM_INVENTORY_H
#define SEM_INVENTORY_H


#include <vector>
//#include "Item.h"
#include <memory>

class Item;

/** Player inventory class.
*/
class Inventory {
private:
    int m_max_size;
    int m_itemCnt;
    std::vector<Item*> m_items;
public:
    Inventory();
    /** Set max inventory size */
    void SetSize(int max);
    /** Remove item from inventory */
    bool RemoveItem(int id);
    /** Add item to inventory */
    bool AddItem(Item* x);
    /** Clear inventory */
    void Clear();
    /** Return inventory */
    std::vector<Item*> GetItems() const;
};


#endif //SEM_INVENTORY_H
