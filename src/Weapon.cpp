
#include "Weapon.h"

//Weapon class
Weapon::Weapon(){
    m_damage = 0;
}
Weapon::Weapon(std::string name, int damage){
    m_name = name;
    m_damage = damage;
}

void Weapon::use(Player& player, int id){
    player.SetDamgeBonus(m_damage);
}
std::string Weapon::GetMessage(){
    return "Weapon equipped";
}
std::string Weapon::GetSaveString(){
    return "weapon " + m_name + " " + std::to_string(m_damage);
}
int Weapon::GetDamage(){
    return m_damage;
}
