//
// Created by siwekm on 30.04.20.
//

#include "World.h"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

int World::GetStartLocationId(){
    return start_location;
}
int World::GetEndLocationId(){
    return end_location;
}
//check if ids where locations are pointing exist
bool World::CheckWorldIntegrity(){
    std::set<int> loc_ids;
    std::set<int> next_ids;
    //get all ids
    for(auto it = locations.begin(); it != locations.end(); it++){
        //locations with same id
        if(loc_ids.find(it->getId()) != loc_ids.end()){
            return false;
        }
        loc_ids.insert(it->getId());
        next_ids.merge(it->GetOptionsIds());
    }
    for(auto it = next_ids.begin(); it != next_ids.end(); it++){
        //location id which is being pointed does not exist
        if(loc_ids.find(*it) == loc_ids.end()){
            return false;
        }
    }
    return true;
}
World::World(const std::string filename){
    std::string line;
    std::ifstream file;
    file.open(filename, std::ios::in);
    if(!file.is_open()){
        std::cout<<"Not open.";
        throw std::exception();
    }
    try {
        while (std::getline (file, line)) {
            if(line=="world"){
                loadWorld(file);
            }
            if(line=="location"){
                addLocation(loadLocation(file));
            }
        }
        file.close();
    }catch(const std::exception &exc){
        std::cout<<"Could not load book data - ivalid file.";
        throw std::exception();
    }
}
bool World::addLocation(Location loc){
    locations.push_back(loc);
    return true;
}
Location& World::GetLocation(int id){
    for(auto it = locations.begin(); it != locations.end(); it++){
        if(it->getId() == id){
            return *it;
        }
    }
    return *locations.begin();
}
Location World::loadLocation(std::ifstream &file){
    std::string line;

    //loadd location index
    std::getline (file, line);
    int loc_index = std::stoi(line.substr(line.find(':') + 1));

    //load world name and description
    std::getline (file, line);
    std::string loc_name = line.substr(line.find(':')+1);

    std::getline (file, line);
    std::string loc_description = line.substr(line.find(':') + 1);

    Weapon weapon = loadWeapon(file);

    Potion potion = loadPotion(file);

    std::getline (file, line);

    if(line!="enemy"){
        //throw error
    }
    Entity enemy = loadEnemy(file);
    Location loc(loc_index, loc_name, loc_description, enemy);
    loc.SetWeapon(weapon);
    loc.SetPotion(potion);

    while (std::getline (file, line)) {
        if (line == "option") {
            Option opt = loadOption(file);
            loc.addOption(opt);
        }else{
            break;
        }
    }
    return loc;
}
Weapon World::loadWeapon(std::ifstream &file){
    std::string line, weapon_name, weapon_damage;
    std::getline (file, line);
    std::stringstream str(line);
    str>>std::ws;
    getline(str, line,':');
    getline(str, weapon_name,':');
    getline(str, weapon_damage,':');

    int damage;
    damage = std::stoi(weapon_damage);
    Weapon weapon(weapon_name, damage);
    return weapon;
}
Potion World::loadPotion(std::ifstream &file){
    std::string line, potion_name, potion__heal, potion_speed;
    std::getline (file, line);
    std::stringstream str(line);
    str>>std::ws;
    getline(str, line,':');
    getline(str, potion_name,':');
    getline(str, potion__heal,':');
    getline(str, potion_speed,':');

    int heal, speed;
    heal = std::stoi(potion__heal);
    speed = std::stoi(potion_speed);
    Potion potion(potion_name, heal, speed);
    return potion;
}
Option World::loadOption(std::ifstream &file){
    std::string line, action, text_fail, text_success;
    int next_fail=0, next_succes=0;

    std::getline (file, line);
    action = line.substr(line.find(':') + 1);

    std::getline (file, line);
    next_succes = std::stoi(line.substr(line.find(':') + 1));

    std::getline (file, line);
    text_success = line.substr(line.find(':') + 1);

    std::getline (file, line);
    text_fail = line.substr(line.find(':') + 1);

    Option opt(action, next_succes, next_fail, text_success, text_fail);
    return opt;
}
bool World::loadWorld(std::ifstream &file){
    std::string line;

    //load world name and description
    std::getline (file, line);
    name = line.substr(line.find(':') + 1);

    std::getline (file, line);
    description = line.substr(line.find(':') + 1);

    //loadd starting location
    std::getline (file, line);
    start_location = std::stoi(line.substr(line.find(':') + 1));

    //load endding location
    std::getline (file, line);
    end_location = std::stoi(line.substr(line.find(':') + 1));
    return true;
}
Entity World::loadEnemy(std::ifstream &file){
    std::string line;

    std::getline (file, line);
    std::string enemy_name = line.substr(line.find(':') + 1);

    std::getline (file, line);
    std::string enemy_stats = line.substr(line.find(':') + 1);
    int n;
    char tmp;
    std::stringstream ss(enemy_stats);
    std::vector<int> attr;

    //load attriutes
    while(ss >> n){
        if(ss >> tmp){}
        attr.push_back(n);
    }
    if(attr.size()<5){
        throw "Not all atributes  specified";
    }
    auto it = attr.begin();
    Entity enemy( *it,*(it+1),*(it+2),*(it+3),*(it+4),enemy_name);
    return enemy;
}
