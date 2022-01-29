//
// Created by siwekm on 22.04.20.
//

#ifndef SEM_ENTITY_H
#define SEM_ENTITY_H


#include <string>
#include <vector>
#include <map>

/** Base Entity class. Used as enemy.
*/
class Entity{
protected:
    std::string m_name;
    int m_health;
    //using std map for accesing attributes by their name
    std::map<std::string,int> attributes;
public:
    Entity();
    Entity(int health, int speed, int strength, int intelligence, int agility, std::string name);
    /** Get entity health. */
    int GetHealth() const;
    /** Set entity health */
    void SetHealth(int health);
    /** Get entity name. */
    std::string GetName() const;
    /** Is entity alive.*/
    bool IsAlive() const;
    /** Get entity entity damage*/
    int Attack();
    /** *Try to run away from enemy.
     * @return true if succesfu */
    bool RunAway(Entity enemy);
    /** Get entity attributes.*/
    std::map<std::string,int> GetAttributes() const;
    /** Set attribute*/
    void SetAttribute(std::pair<std::string, int> att);
};

#endif //SEM_ENTITY_H
