#include <iostream>


using namespace std;

int main()
{	// Opening Statement
	cout << "Choose Only One number: Rock (1), Paper (2), Scissors (3). To exit enter 0 " << endl;

	// Looping the program
	while (true) {
		// Defined Variables
		int RPS;
		int result = 1 + rand() % 3; // random


		// Input for Rock, Paper, Scissors as digits
		cin >> RPS;


		// Exit from console
		if (RPS == 0) {
			break;
		}
		if (RPS > 3 || RPS < 1) {
			cout << "Invalid Response!! Choose number from 1-3" << endl;
			break;
		}
		// Identified objects
		if (result == 1) {
			cout << "Rock" << endl;
		} else if (result == 2) {
			cout << "Paper" << endl;
		} else if (result == 3) {
			cout << "Scissors" << endl;
		}

		// Glory Prompt
		if (result == 1 && RPS == 1) {
			cout << "It is a Tie" << endl;
		} else if (result == 2 && RPS == 1) {
			cout << "You Lost" << endl;
		} else if (result == 3 && RPS == 1) {
			cout << "You Won!" << endl;
		}
		if (result == 1 && RPS == 2) {
			cout << "You Won!" << endl;
		} else if (result == 2 && RPS == 2) {
			cout << "It is a Tie" << endl;
		} else if (result == 3 && RPS == 2) {
			cout << "You Lost" << endl;
		}
		if (result == 1 && RPS == 3) {
			cout << "You Lost" << endl;
		} else if (result == 2 && RPS == 3) {
			cout << "You win" << endl;
		} else if (result == 3 && RPS == 3) {
			cout << "It is a Tie" << endl;
		}
	}

}

