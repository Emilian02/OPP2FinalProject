#include<iostream>
#include<thread>
#include<chrono>
#include<time.h>
#include "Players.h"

using namespace std;


void loadingPlayers(Players& player) {
	int waitTime = rand() % 10 + 1;

	cout << player.getName() << " has joined the lobby" << endl;

	this_thread::sleep_for(chrono::seconds(waitTime));
}

void loadingGame() {
	std::cout << "Loading game..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(4)); 
	std::cout << "Game loaded. Transitioning to gameplay..." << std::endl;
}

void startingGame() {
	int waitTime = rand() % 10 + 1;

	thread loadingThread(loadingGame);

	loadingThread.join();

	cout << "Entering gameplay..." << endl;

	this_thread::sleep_for(chrono::seconds(waitTime));
	
	system("CLS");
}

void testing() {
	string name1;

	cout << "Enter the name for your character: ";
	getline(cin, name1);

	Players player1(name1);
	Players player2("Abdullah");
	Players player3("N");
	Players player4("Camu");

	loadingPlayers(player1);
	loadingPlayers(player2);
	loadingPlayers(player3);
	loadingPlayers(player4);

	startingGame();

	cout << "-------------------Storage-------------------" << endl << endl;

}

int main() {
	srand(time(NULL));

	testing();
}