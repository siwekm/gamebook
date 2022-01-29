#include "Saver.h"
#include "Item.h"
#include <memory>

void Saver::Save(Player player, std::string saveFile){
    std::string line;
    std::ofstream file;
    file.open(saveFile, std::ios::trunc);

    if(!file.is_open()){
        return;
    }
    file<<player.GetLocationId()<<std::endl;
    file<<player.GetName()<<std::endl;
    file<<player.GetHealth()<<std::endl;

    auto attributes = player.GetAttributes();
    for (auto it = attributes.begin();  it != attributes.end() ; it++){
        file<<it->second<<std::endl;
    }
    //save all items
    std::vector<Item*> tmpInv = player.inv.GetItems();
    for(auto it = tmpInv.begin(); it != tmpInv.end(); it++){
        file<<(*it)->GetSaveString()<<std::endl;
    }
    file.close();
}

void Saver::Load(Player& player, std::string saveFile){
    int tmpInt;
    std::string tmpStr;

    std::string line;
    std::ifstream file;
    file.open(saveFile, std::ios::in);

    if(!file.is_open()){
        throw std::exception();
    }
    std::string tmpName;
    int tmpHeal = 0, tmpSpeed = 0;
    player.inv.SetSize(10);
    file>>tmpInt;
    player.SetLocation(tmpInt);
    file>>tmpStr;
    player.SetName(tmpStr);
    file>>tmpInt;
    player.SetHealth(tmpInt);
    file>>tmpInt;
    player.SetAttribute(std::pair("agility", tmpInt));
    file>>tmpInt;
    player.SetAttribute(std::pair("intelligence", tmpInt));
    file>>tmpInt;
    player.SetAttribute(std::pair("speed", tmpInt));
    file>>tmpInt;
    player.SetAttribute(std::pair("strength", tmpInt));
    int tmpDamage;
    //load all items
    std::string type;
    while(file>>type){
        if(type == "potion"){
            file>>tmpName>>tmpHeal>>tmpSpeed;
            Potion* pot = new Potion(tmpName, tmpHeal, tmpSpeed);
            player.inv.AddItem(pot);
        }else if(type == "weapon"){
            file>>tmpName>>tmpDamage;
            Weapon* wpn = new Weapon(tmpName, tmpDamage);
            player.inv.AddItem(wpn);
        }else{
            return;
        }
    }
    file.close();
}