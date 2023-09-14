#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
#include <mutex>
#include <atomic>
#include "Players.h"

using namespace std;

atomic<bool> gameEnded(false); // To track the game state
mutex gameMutex; // Mutex for protecting shared data


vector<Players> playersData;

void displayPlayerProgress(const Players& player) {
    while (!gameEnded) {
        this_thread::sleep_for(chrono::seconds(20));
        cout << endl << endl << endl;
        cout << player.getName() << " progress: " << player.getProgress() << "%" << endl;
        this_thread::sleep_for(chrono::seconds(20));
    }
}

// Function to simulate player progress independently
void simulatePlayerProgress(Players& player) {
    while (!gameEnded) {
        int increment = rand() % 24 + 1; // Random increment between 1 and 24
        player.addProgress(increment); // Add the increment to the player's progress

        this_thread::sleep_for(chrono::seconds(30));
    }
}

// Loading section
void loadingPlayers(Players& player) {
    int waitTime = rand() % 10 + 1;

    cout << player.getName() << " has joined the lobby" << endl;

    this_thread::sleep_for(chrono::seconds(waitTime));
}

void loadingGame() {
    cout << "Loading game..." << std::endl;
    this_thread::sleep_for(chrono::seconds(4));
    cout << "Game loaded. Transitioning to gameplay..." << std::endl;
}

void startingGame() {
    thread loadingThread(loadingGame);

    loadingThread.join();

    cout << "Entering gameplay..." << endl;

    this_thread::sleep_for(chrono::seconds(5));

    system("CLS");
}

// Function to check for a winner
void checkForWinner() {
    for (const Players& progress : playersData) {
        if (progress.getProgress() == 100) {
            cout << progress.getName() << " is the winner!" << endl;
            return; // Exit the function when a winner is found
        }
    }
}

// Main game logic
void testing() {
    string name1;

    //Creeating the instances

    cout << "Enter the name for your character: ";
    getline(cin, name1);

    Players player1(name1);
    Players player2("Abdullah");
    Players player3("N");
    Players player4("Camu");

    //Simulating the players joining
    loadingPlayers(player1);
    loadingPlayers(player2);
    loadingPlayers(player3);
    loadingPlayers(player4);

    //Having the progress of the other players
    playersData.push_back(player2);
    playersData.push_back(player3);
    playersData.push_back(player4);

    startingGame();

    // Creating threads to simulate player progress
    thread Player2Progress(simulatePlayerProgress, ref(player2));
    thread Player3Progress(simulatePlayerProgress, ref(player3));
    thread Player4Progress(simulatePlayerProgress, ref(player4));

    // Creating threads to display player progress
    thread Player2Display(displayPlayerProgress, ref(player2));
    thread Player3Display(displayPlayerProgress, ref(player3));
    thread Player4Display(displayPlayerProgress, ref(player4));

    // Picking and using items
    int option;

    cout << "-------------------Storage-------------------" << endl << endl;

    player1.addItem("Step Ladder", 2);

    do {
        cout << "Where should I look?" << endl
            << "[1] Check the top of the shelf" << endl
            << "[2] Inspect the hanging box" << endl
            << "[3] Check the door" << endl;
        cout << "Choose: ";
        cin >> option;

        if (option == 1) {
            if (player1.useItem(2)) {
                cout << "You've obtained a dagger" << endl << endl;
                player1.addItem("Dagger", 4);
            }
            else {
                cout << "I can't reach the top" << endl << endl;
            }

            // To check if the item was added
            player1.displayInventory();

            system("Pause");
            system("CLS");
        }
        else if (option == 2) {
            if (player1.useItem(4)) {
                cout << "The box fell down and you've obtained the exit key" << endl << endl;
                player1.addItem("Exit Key", 1);
            }
            else {
                cout << "Looks like I'll need something to cut the rope" << endl << endl;
            }

            // To check if the item was added
            player1.displayInventory();

            system("Pause");
            system("CLS");
        }
        else if (option == 3) {
            if (player1.useItem(1)) {
                cout << "You've escaped the dungeon" << endl << endl;

                player1.setProgress(100); // Set progress to 100% when a player escapes
                gameEnded = true; // Update the game state to end the game
                break;
            }
            else {
                cout << "The door is locked" << endl << endl;
            }
        }
        else {
            cout << "Invalid input" << endl << endl;
        }

        checkForWinner();

    } while (option != 0);

    // Check for a winner once after the game loop ends
    checkForWinner();

    Player2Progress.join();
    Player3Progress.join();
    Player4Progress.join();
    
    Player2Display.join();
    Player3Display.join();
    Player4Display.join();

    // End the game properly
    gameEnded = true;


    cout << "Game has ended" << endl;
}

int main() {
    srand(time(NULL));

    testing();

    return 0;
}
