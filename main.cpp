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
	cout << "Loading game..." << std::endl;
	this_thread::sleep_for(std::chrono::seconds(4)); 
	cout << "Game loaded. Transitioning to gameplay..." << std::endl;
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

	//Picking and using item
	int option;

	cout << "-------------------Storage-------------------" << endl << endl;

	//I'm starting at a random point. I testing if picking up items work and using them. Seeing if the conditions work right

	player1.addItem("Step Ladder", 2);

	do {
		cout << "Where shoudl I look?" << endl
			<< "[1] Check a top of the shelf" << endl
			<< "[2] Inspect hanging box" << endl
			<< "[3] Check the door" << endl;
		cout << "Choose: ";
		cin >> option;

		if (option == 1) {
			if (player1.useItem(2)) {
				cout << "You've obtained a dagger" << endl << endl;
				player1.addItem("Dagger", 4);
			}
			else{
				cout << "I can't reach the top" << endl << endl;
			}

			//To check if the item was added
			player1.displayInventory();

			system("Pause");
			system("CLS");
		}
		else if (option == 2) {
			if (player1.useItem(4)) {
				cout << "The box felled down and you've obtained the exit key" << endl << endl;
				player1.addItem("Exit Key", 1);
			}
			else {
				cout << "Looks like I'll need something to cut the rope" << endl << endl;
			}

			//To check if the item was added
			player1.displayInventory();

			system("Pause");
			system("CLS");
		}
		else if (option == 3) {
			if (player1.useItem(1)) {
				cout << "You've escaped the dungeon" << endl << endl;
				break;
			}
			else {
				cout << "The door is locked" << endl << endl;
			}

		}
		else {
			cout << "Invalid input" << endl << endl;
		}

	} while (option != 0);
	

	

}

int main() {
	srand(time(NULL));

	testing();
}