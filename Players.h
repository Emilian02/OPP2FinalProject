#ifndef PLAYERS_H
#define PLAYERS__H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

class Players {
private:
    string name;
    int progress; 
    string inventory[13]; 

public:

    Players() : name(""), progress(0){
        for (int i = 0; i < 13; ++i) {
            inventory[i] = "";
        }
    }

    Players(string playerName) : name(playerName), progress(0) {

        for (int i = 0; i < 13; ++i) {
            inventory[i] = "";
        }
    }


    ~Players() {};

    string getName() const {
        return name;
    }

    void addItem(string item, int index) {
        inventory[index] = item;
    }

    void displayInventory() {
        cout << "----------------- Inventory of " << name << ": -----------------" << endl;
        for (int i = 0; i < 13; ++i) {
            if (inventory[i] != "") {
                cout << "- " << inventory[i] << endl;
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

    // Method to add progress to the player's current progress
    void addProgress(int increment) {
        progress += increment;
        if (progress > 100) {
            progress = 100;
        }
    }

    void setProgress(int progress) {
        this->progress = progress;
    }

    int getProgress() const {
        return progress;
    }
};



#endif 

