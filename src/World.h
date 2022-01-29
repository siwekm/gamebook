//
// Created by siwekm on 30.04.20.
//

#ifndef SEM_WORLD_H
#define SEM_WORLD_H


#include <string>
#include "Entity.h"
#include "Location.h"
#include "Weapon.h"
#include "Potion.h"

/** Stores all locations and world data. Loads world data from file.*/
class World {
private:
    int start_location;
    int end_location;
    std::string name;
    std::string description;
    /** load world book from file*/
    bool loadWorld(std::ifstream &file);
    /** Add new location*/
    bool addLocation(Location loc);
    /** load location data */
    Location loadLocation(std::ifstream &file);
    /** load weapon data */
    Weapon loadWeapon(std::ifstream &file);
    /** load potion data */
    Potion loadPotion(std::ifstream &file);
    /** load option data*/
    Option loadOption(std::ifstream &file);
    /** load enemy data*/
    Entity loadEnemy(std::ifstream &file);
public:
    //vector of world locations
    std::vector<Location> locations;
    World(const std::string filename);
    /** Get id of starting location. */
    int GetStartLocationId();
    /** Get id of last location. */
    int GetEndLocationId();
    /** Checks if every pointed id location exists.
     * @return False if id does not exist.
     */
    bool CheckWorldIntegrity();
    /** Return location by id */
    Location& GetLocation(int id);
};


#endif //SEM_WORLD_H
