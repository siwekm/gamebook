//
// Created by siwekm on 27.05.20.
//

#include "Item.h"

//Item class

std::string Item::GetName() const{
    return m_name;
}
void Item::SetName(std::string name){
    m_name = name;
}

