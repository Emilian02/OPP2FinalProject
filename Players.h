#ifndef PLAYERS_H
#define PLAYERS__H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Players {
private:
    string name;
    int time;
    string inventory[13]; 

public:
    Players(string playerName) : name(playerName), time(1800) {

        for (int i = 0; i < 10; ++i) {
            inventory[i] = "";
        }
    }

    string getName() {
        return name;
    }

    void addItem(string item, int index) {
        inventory[index] = item;
    }

    void displayInventory() {
        cout << "----------------- Inventory of " << name << ": -----------------" << endl;
        for (int i = 0; i < 13; ++i) {
            if (inventory[i] != "") {
                cout << inventory[i] << endl;
            }
        }
    }

    bool useItem(int index) {
        if (inventory[index] != "") {
            cout << name << " used item: " << inventory[index] << endl;
            return true;
        }
        else {
            return false;
        }
    }
};



#endif 

