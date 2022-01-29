#include "Potion.h"

//Potion class
Potion::Potion(){
    m_heal = 0;
    m_speed = 0;
}
Potion::Potion(std::string name,int heal, int speed){
    m_name = name;
    m_heal = heal;
    m_speed = speed;
}
void Potion::use(Player& player, int id){
    player.SetHealth(player.GetHealth()+m_heal);
    player.inv.RemoveItem(id);
}
std::string Potion::GetMessage(){
    return "Potion used.";
}
std::string Potion::GetSaveString(){
    return "potion " +  m_name + " " + std::to_string(m_heal) + " " + std::to_string(m_speed);
}
int Potion::GetHeal() const{
    return m_heal;
}
int Potion::GetSpeed() const{
    return m_speed;
}