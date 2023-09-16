#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
#include <mutex>
#include <atomic>
#include <random>
#include <iomanip>
#include "Players.h"

using namespace std;

atomic<bool> gameEnded(false); // To track the game state
mutex gameMutex; // Mutex for protecting shared data


vector<Players> playersData;


// Function to notify players about progress
void notifyPlayer() {
    while (!gameEnded) {
        this_thread::sleep_for(chrono::seconds(30)); // Adjust the update interval as needed

        if (gameEnded) {
            break;
        }

        cout << endl << endl;
        for (int i = 1; i < 4; i++) {
            cout << setw(15) << left << playersData[i].getName() << " progress: "
                << setw(7) << right << fixed << setprecision(2) << playersData[i].getProgress() << "%" << endl;
        }
    }
}

// Function to simulate player progress independently
void simulatePlayerProgress(Players& player) {
    // Define a random number generator and distribution
    random_device rd;
    mt19937 gen(rd()); // Mersenne Twister random number engine
    uniform_real_distribution<double> dis(1, 25); // Range [1, 25]
    while (!gameEnded) {
        double increment = dis(gen);
        player.addProgress(increment); // Add the increment to the player's progress
         // Update the progress in the vector playersData
        for (Players& p : playersData) {
            if (p.getName() == player.getName()) {
                p.setProgress(player.getProgress());
                break;
            }
        }
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
            // End the game properly
            gameEnded = true;
            return; // Exit the function when a winner is found
        }
    }
}

void checkForWinnerPeriodically() {
    while (!gameEnded) {
        checkForWinner();
        this_thread::sleep_for(chrono::seconds(5)); 
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
    playersData.push_back(player1);
    playersData.push_back(player2);
    playersData.push_back(player3);
    playersData.push_back(player4);

    startingGame();

    // Creating threads to simulate player progress
    thread Player2Progress(simulatePlayerProgress, ref(player2));
    thread Player3Progress(simulatePlayerProgress, ref(player3));
    thread Player4Progress(simulatePlayerProgress, ref(player4));

    //Thread for notifying
    thread notification(notifyPlayer);
    
    // Create a thread for checking the win condition
    thread winnerThread(checkForWinnerPeriodically);
    

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
                playersData[0].setProgress(100);// Set progress to 100% when a player escapes
                checkForWinner();
                /*gameEnded = true;*/
                break;
            }
            else {
                cout << "The door is locked" << endl << endl;
                player1.displayInventory();

                system("Pause");
                system("CLS");
            }
        }
        else {
            cout << "Invalid input" << endl << endl;
        }


    } while (!gameEnded);


    Player2Progress.join();
    Player3Progress.join();
    Player4Progress.join();

    notification.join();

    winnerThread.join();

    cout << "The game has ended" << endl;


}

int main() {
    srand(time(NULL));

    testing();

    return 0;
}
