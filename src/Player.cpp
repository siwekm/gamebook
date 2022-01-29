//
// Created by siwekm on 22.04.20.
//

#include <fstream>
#include <iostream>
#include "Player.h"

Player::Player(std::string name){
    m_name = name;
    current_location = 0;
}
void Player::SetName(std::string name){
    m_name =  name;
}
void Player::SetHealth(int health){
    m_health = health;
}
void Player::SetLocation(int loc){
    current_location = loc;
}
int Player::GetLocationId() const{
    return current_location;
}
int Player::Attack(){
    return attributes["strength"] + attributes["intelligence"] + m_damage_bonus;
}
bool Player::Fight(Entity target){
    while(m_health > 0){
        if(target.GetHealth() <= 0){
            return true;
        }
        target.SetHealth(target.GetHealth()-Attack());
        SetHealth(m_health-target.Attack());
    }
    return false;
}
bool Player::RunAway(Entity enemy){
    return attributes["speed"] + attributes["agility"] > enemy.GetAttributes()["speed"] + enemy.GetAttributes()["agility"];
}
void Player::SetDamgeBonus(int dmg){
    m_damage_bonus = dmg;
}
int Player::GetDamageBonus() const{
    return m_damage_bonus;
}
