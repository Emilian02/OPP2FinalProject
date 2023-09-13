#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// Dummy Player class
class Player {
public:
    string name;
    int health;
    // Add other player attributes as needed

    Player(const string& _name) : name(_name), health(100) {}
};

// Server side
vector<Player> lobby;

// Simulate player joining the lobby
void PlayerJoinsLobby(Player newPlayer) {
    lobby.push_back(newPlayer);

    cout << "Player " << newPlayer.name << " has joined the lobby." << endl;

    this_thread::sleep_for(chrono::seconds(4)); //Simulating players joining
}

// Check if there are enough players to start the game
bool CanStartGame() {
    return lobby.size() >= 2; // Adjust the minimum player count as needed
}


// Client side
// Dummy function to create a Player object representing the client
Player CreatePlayer(const string& playerName) {
    return Player(playerName);
}

// Simulate connecting to the server and joining the lobby
void ConnectToServer(const string& playerName) {
    // Connect to the server (simulated)
    cout << "Connected to the server." << endl;

    // Create a Player object representing the client
    Player clientPlayer = CreatePlayer(playerName);

    // Join the lobby
    PlayerJoinsLobby(clientPlayer);
}


//Creating instance of a thread to implememnt loading
void LoadingThread() {
    if (CanStartGame()) {
        std::cout << "Loading game..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate a 3-second loading time
        std::cout << "Game loaded. Transitioning to gameplay..." << std::endl;
        // Perform actual loading tasks here
    }
    else {
        std::cout << "Waiting for more players to join..." << std::endl;
    }
}

void StartGame() {
    if (CanStartGame()) {
        // Create a thread for loading
        std::thread loadingThread(LoadingThread);

        // Continue processing other tasks in the main thread
        std::cout << "Main thread continues to process tasks..." << std::endl;

        // Wait for the loading thread to finish
        loadingThread.join();

        // Transition to gameplay
        std::cout << "Entering gameplay..." << std::endl;
        // Implement gameplay logic here
    }
    else {
        std::cout << "Cannot start the game yet. Waiting for more players..." << std::endl;
    }
}

//Simple way to similute loading screen

//// Loading process
//void StartLoadingGame() {
//    if (CanStartGame()) {
//        cout << "Loading game..." << endl;
//        // Simulate loading (e.g., introduce a delay)
//        this_thread::sleep_for(chrono::seconds(7)); // Simulate a loading time
//
//        // Perform loading tasks (initialize game world, distribute items, etc.)
//        cout << "Game loaded. Transitioning to gameplay..." << endl;
//        // Transition to gameplay
//    }
//    else {
//        cout << "Waiting for more players to join..." << endl;
//    }
//}
//
//// Simulate starting the game when the server indicates
//void StartGame() {
//    if (CanStartGame()) {
//        StartLoadingGame();
//    }
//    else {
//        cout << "Cannot start the game yet. Waiting for more players..." << endl;
//    }
//}

int main() {
    string name1;

    cout << "Enter the name for your character: ";
    cin >> name1;

    // Simulate two players connecting to the server
    ConnectToServer(name1);
    ConnectToServer("Player2");

    // Attempt to start the game
    StartGame();

    return 0;
}
