//
// Created by siwekm on 10.05.20.
//

#include "Game.h"
#include "PlayerCreator.h"
#include "Location.h"
#include "Saver.h"
#include <ncurses.h>

Game::Game(std::string file_name) : gameWorld(file_name) {
    //initialize ncurses
    initscr();
    noecho();
    cbreak();
}
void Game::SetupPlayer(){
    PlayerCreator creator(gamePlayer);
    gamePlayer.SetAttribute(std::pair("speed", 1));
    gamePlayer.SetAttribute(std::pair("strength", 1));
    gamePlayer.SetAttribute(std::pair("intelligence", 1));
    gamePlayer.SetAttribute(std::pair("agility", 1));
    endwin();
    creator.SetName();
    creator.Show();

    gamePlayer.SetHealth(maxHealth);
    gamePlayer.SetLocation(gameWorld.GetStartLocationId());
    gamePlayer.inv.SetSize(maxInvSize);
    gamePlayer.inv.Clear();
}
void Game::Play() {
    if(!gameWorld.CheckWorldIntegrity()){
        DisplayMessage("Invalid world data - pointed location ID not found - ");
        return;
    }

    while(gamePlayer.GetLocationId() != gameWorld.GetEndLocationId()){
        Location& currentLoc = gameWorld.GetLocation(gamePlayer.GetLocationId());
        int select = DisplayLocation(currentLoc);
        DisplayPlayerInventory();

        if (select == 0){
            if(gamePlayer.Fight(currentLoc.m_enemy)){
                //won fight, add drops to inventory
                DisplayWeapon(*currentLoc.GetWeapon());
                Item* tmp = currentLoc.GetPotion();
                gamePlayer.inv.AddItem(tmp);
                tmp = currentLoc.GetWeapon();
                gamePlayer.inv.AddItem(tmp);
            }
        }else{
            if(!gamePlayer.RunAway(currentLoc.m_enemy)){
                gamePlayer.SetHealth(0);
            }
        }
        Option opt = *(currentLoc.GetOptions().begin()+select);

        if(gamePlayer.IsAlive()){
            DisplayMessage(opt.GetTextSuccess());
            gamePlayer.SetLocation(opt.GetNextSuccess());
        }else{
            DisplayMessage(opt.GetTextFail());
            Death();
            return;
        }
    }
    DisplayMessage(gameWorld.GetLocation(gameWorld.GetEndLocationId()).GetDescription());
    DisplayMenu();
}
void Game::DisplayMenu(){
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax); //get sreen size

    WINDOW *menu = newwin(yMax, xMax, 0, 0); //create window
    box(menu, 0,0);
    refresh();
    wrefresh(menu);

    keypad(menu, true);
    std::vector<std::string> options = {"Play", "Load", "How to play", "Exit"};

    int row = 10;
    int selected = 0;
    int key;
    do{
        int i=0;
        //display all options, highlight selected
        for(auto it = options.begin(); it != options.end(); it++){
            if(selected == i){
                wattron(menu, A_REVERSE);
            }
            mvwprintw(menu, row+i, 10, it->c_str());
            wattroff(menu, A_REVERSE);
            i++;
        }
        refresh();
        wrefresh(menu);
        key = wgetch(menu);

        switch(key){
            case KEY_UP://up
                if (selected > 0){
                    selected--;
                }
                break;
            case KEY_DOWN://down
                if ((unsigned long)selected < options.size() - 1){
                    selected++;
                }
                break;
        }
    }while(key != '\n');

    if(selected == 0){
        SetupPlayer();
        Play();
    }else if(selected == 1){
        gamePlayer.inv.SetSize(maxInvSize);
        gamePlayer.inv.Clear();
        try{
            endwin();
            std::string save_file;
            std::cout<<"Select save file:"<<std::endl;
            std::cin>>save_file;
            Saver svr;
            svr.Load(gamePlayer, save_file);
        }catch (const std::exception &exc){
            DisplayMessage("Invalid save file.");
            DisplayMenu();
            return;
        }
        Play();
    }else if(selected == 2){
        DisplayTutorial();
    }

    endwin();
    return;
}
void Game::DisplayTutorial(){
    DisplayMessage("Player stats are displayed on top of the screen.");
    DisplayMessage("Location info is displayed. Enemy stats are below.");
    DisplayMessage("For each location player options are displayed.");
    DisplayMessage("Before selected option is performed inventory is displayed.");
    DisplayMessage("Press 'x' to use item. Enter to perform selected option.");
    DisplayMessage("After fighting enemy player will move to the next location or die.");
    DisplayMenu();
}
void Game::DisplayPlayerInventory(){
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax); //get sreen size
    WINDOW *menu = newwin(yMax, xMax, 0, 0); //create window
    keypad(menu, true);

    box(menu, 0,0);
    refresh();
    wrefresh(menu);
    int selected = 0;
    int key,i;
    do{
        std::vector<Item*> invArr = gamePlayer.inv.GetItems();
        int row = yMax/3;
        i = 0;
        wclear(menu);
        wrefresh(menu);
        mvprintw(row-2, 5, "Inventory");
        for(auto it = invArr.begin(); it != invArr.end(); it++){
            if(selected == i){
                wattron(menu, A_REVERSE);
            }
            mvwprintw(menu,row+i, 5, (*it)->GetName().c_str());
            wattroff(menu, A_REVERSE);
            i++;
        }
        mvwprintw(menu,yMax-2, 4, "Press x to use the item. Enter to continue...");
        refresh();
        wrefresh(menu);
        key = wgetch(menu);

        switch(key){
            case KEY_UP://up
                if (selected > 0){
                    selected--;
                }
                break;
            case KEY_DOWN://down
                if ((unsigned long)selected < invArr.size() - 1){
                    selected++;
                }
                break;
            case 'x'://to use the potion
                (*(invArr.begin()+selected))->use(gamePlayer, selected);
                DisplayMessage((*(invArr.begin()+selected))->GetMessage());
                break;
        }
    }while(key != '\n');

    endwin();
}
void Game::DisplayMessage(std::string msg){
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax); //get sreen size

    WINDOW *menu = newwin(yMax, xMax, 0, 0); //create window
    box(menu, 0,0);
    refresh();
    wrefresh(menu);
    mvprintw(yMax/2, 5, msg.c_str());
    refresh();
    wrefresh(menu);
    getch();
    endwin();
}
void Game::DisplayPlayerStats(){
    int row = 1, col = 1;
    mvprintw(row++, col, gamePlayer.GetName().c_str());
    row++;
    mvprintw(row, col, "health");
    mvprintw(row++, col+15, "%d", gamePlayer.GetHealth());

    std::map<std::string,int>  attr = gamePlayer.GetAttributes();

    for(auto it = attr.begin(); it != attr.end(); it++){
        mvprintw(row, col, it->first.c_str());
        mvprintw(row++, col+15, "%d", it->second);
    }
}
int Game::DisplayLocation(Location tmp){
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax); //get sreen size

    WINDOW *menu = newwin(yMax, xMax, 0, 0); //create window
    box(menu, 0,0);
    refresh();
    wrefresh(menu);
    keypad(menu, true);

    auto opts = tmp.GetOptions();
    int selected = 0;
    int key;
    do{
        DisplayPlayerStats();
        int row = 10;
        mvprintw(row++, 1, tmp.GetName().c_str());
        mvprintw(row++, 1, tmp.GetDescription().c_str());
        mvprintw(row++, 1, tmp.m_enemy.GetName().c_str());
        mvprintw(row++, 1, "Health:");
        mvprintw(row++, 1, "%d", tmp.m_enemy.GetHealth());

        int i=0;
        //display all options, highlight selected
        for(auto it = opts.begin(); it != opts.end(); it++){
            if(selected == i){
                wattron(menu, A_REVERSE);
            }
            mvwprintw(menu, row+i, 10, it->GetAction().c_str());
            wattroff(menu, A_REVERSE);
            i++;
        }
        mvwprintw(menu, yMax-3, 10, "Press s to save.");
        refresh();
        wrefresh(menu);
        key = wgetch(menu);

        switch(key){
            case KEY_UP://up
                if (selected > 0){
                    selected--;
                }
                break;
            case KEY_DOWN://down
                if ((unsigned long)selected < opts.size() - 1){
                    selected++;
                }
                break;
            case 's':
                Saver svr;
                svr.Save(gamePlayer, "save.txt");
                DisplayMessage("Game saved.");
        }
    }while(key != '\n');

    endwin();
    return selected;
}
void Game::DisplayWeapon(Weapon wpn){
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax); //get sreen size

    WINDOW *menu = newwin(yMax, xMax, 0, 0); //create window
    box(menu, 0,0);
    refresh();
    wrefresh(menu);
    int row = 10, col = 2;
    mvwprintw(menu, row++, col,"You have found");
    mvwprintw(menu, row++, col, wpn.GetName().c_str());
    mvwprintw(menu, row++, col,"Damage:");
    mvwprintw(menu, row++, col, "%d", wpn.GetDamage());
    endwin();
    return;
}
void Game::Death(){
    DisplayMessage("You have died.");
    DisplayMenu();
}