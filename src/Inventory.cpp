//
// Created by siwekm on 27.05.20.
//

#include "Inventory.h"

Inventory::Inventory(){
    m_max_size = 0;
    m_itemCnt = 0;
}
void Inventory::SetSize(int max){
    m_max_size = max;
}
bool Inventory::AddItem(Item* x){
    if(m_items.size() >= (unsigned long)m_max_size){
        return false;
    }
    m_items.push_back(x);
    return true;
}
bool Inventory::RemoveItem(int id){
    if((unsigned long)id > m_items.size() || id < 0){
        return false;
    }
    m_items.erase(m_items.begin()+id);
    return true;
}
std::vector<Item*> Inventory::GetItems() const{
    return m_items;
}
void Inventory::Clear(){
    m_items.clear();
}
