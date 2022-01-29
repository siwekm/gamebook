//
// Created by siwekm on 22.04.20.
//

#include "Entity.h"

Entity::Entity(){
    m_health = 0;
    attributes.insert({"speed", 1});
    attributes.insert({"strength", 1});
    attributes.insert({"intelligence", 1});
    attributes.insert({"agility", 1});
    m_name = "Entity";
}
Entity::Entity(int health, int speed, int strength, int intelligence, int agility, std::string name){
    m_health = health;
    attributes.insert({"speed", speed});
    attributes.insert({"strength", strength});
    attributes.insert({"intelligence", intelligence});
    attributes.insert({"agility", agility});
    m_name = name;
}
int Entity::GetHealth() const{
    return m_health;
}
void Entity::SetHealth(int health){
    m_health = health;
}
std::string Entity::GetName() const{
    return m_name;
}
int Entity::Attack(){
    return attributes["strength"]+attributes["intelligence"];
}
bool Entity::RunAway(Entity enemy){
    return attributes["speed"] + attributes["agility"] > enemy.attributes["speed"] + enemy.attributes["agility"];
}
bool Entity::IsAlive() const{
        if(m_health > 0){
            return true;
        }
        return false;
}
std::map<std::string,int> Entity::GetAttributes() const{
    return attributes;
}
void Entity::SetAttribute(std::pair<std::string, int> att){
    attributes[att.first] = att.second;
}