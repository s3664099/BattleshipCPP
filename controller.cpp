#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

int getNumber(string query,int min, int max);
void addShips(Board *user,int num, int boardSize);

int getNumber(string query,int min, int max) {

	bool correct = false;
	int response = 0;

	while (!correct) {

		std::cout<<query<<": ";
		std::cin>>response;
		std::cout<<endl;

		if (cin.fail()) {

		    // user didn't input a number
		    cin.clear(); // reset failbit
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout<<"Please enter a number"<<std::endl;

		} else if ((response > max) || (response < min)) {
			std::cout<<"Please enter a number between "<<min<<" and "<<max<<std::endl;
		} else {
			correct = true;
		}
		
	}

	return response;
}

//Process to add ships for a manual player
void addShips(Board *user,int num,int boardSize) {

	std::vector<Ship>* ships = user->getShips();
	user->setManualPlayer();

	//Sets up the player's name
	std::string playerNumber = "one";
	if (num == 2) {
		playerNumber = "two";
	}
	std::string userName = "";
	std::cout<<"Please enter player "<<playerNumber<<"'s name: ";
	std::cin>>userName;

	//Has the player entered a name?
	if (userName.length()<1) {
		if(num == 1) {
			userName = "Nameless Player";
		} else {
			userName = "Player without a Name";
		}
	}

	user->setName(userName);

	//Process to add ships
	for (Ship ship:*ships) {

		//Creates a set to hold the potential places the ship can be placed
		set<Coordinate> potentialPlace;

		displayGrid(10,user->getGrid());
	}
}