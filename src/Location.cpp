//
// Created by siwekm on 30.04.20.
//

#include "Location.h"

Option::Option(std::string action, int next_success, int next_fail, std::string text_success,  std::string text_fail)
    : m_action(action), m_next_success(next_success), m_next_fail(next_fail), m_text_success(text_success), m_text_fail(text_fail) {}

int Option::GetNextSuccess() const{
    return m_next_success;
}
int Option::GetNextFail() const{
    return m_next_fail;
}
std::string Option::GetAction() const{
    return m_action;
}
std::string Option::GetTextSuccess() const{
    return  m_text_success;
}
std::string Option::GetTextFail() const{
    return m_text_fail;
}

Location::Location(int id, std::string &name, std::string &desc, Entity &enemy) : m_id(id), m_name(name), m_description(desc), m_enemy(enemy){}
void Location::addOption(Option opt){
    options.push_back(opt);
}
int Location::getId() const{
    return m_id;
}
std::set<int> Location::GetOptionsIds() const{
    std::set<int> ids;
    for(auto it = options.begin(); it != options.end(); it++){
        ids.insert(it->GetNextFail());
        ids.insert(it->GetNextSuccess());
    }
    return ids;
}
std::vector<Option> Location::GetOptions() const{
    return options;
}
std::string Location::GetName() const{
    return m_name;
}
std::string Location::GetDescription() const{
    return m_description;
}
bool Location::HasEnemy() const{
    return m_enemy.IsAlive();
}
void Location::SetWeapon(Weapon x){
    m_weaponDrop = x;
}
void Location::SetPotion(Potion x){
    m_potionDrop = x;
}
Weapon* Location::GetWeapon(){
    return &m_weaponDrop;
}
Potion* Location::GetPotion(){
    return  &m_potionDrop;
}
