#include <string>
#include <set>
#include <vector>
#include <ctime>
#include "ship.cpp"
using namespace std;

class Board{

	private:
		int rows;
    	std::vector<std::vector<std::string>> grid;
    	std::vector<std::vector<std::string>> spotsHit;
		string objectName;
		int gridSize;
		set <Coordinate> potentialShots;
		set <Coordinate> usedSpots;
		set <int> shipShots;
		std::vector <Ship>* ships;
		int hitShip;
		Coordinate hit;
		Coordinate originalHit;
		int movement;
		bool manualPlayer;
		void addShip(Ship& ship);
		Ship* checkShipHit(Coordinate coOrds, string playerName);
		void removeShip(Ship* shipToRemove);
		bool checkRemainingShips();
		void markGrid(set<Coordinate>* sectionsToMark);

	public:
		Board(string objectName, int size);
		string getName();
		int getSize();
		void setName(string objectName);
		std::vector<std::vector<std::string>>* getGrid();
		std::vector<std::vector<std::string>>* getSpotsHit();
		set<Coordinate> getPotentialShots();
		void setPotentialShots(set<Coordinate> potentialShots);
		set<int> getShipShots();
		void setShipShots(set<int> shipShots);
		void setHitShip(int hitShip);
		int getHitShip();
		void setHit(Coordinate hit);
		Coordinate getHit();
		void setMovement(int movement);
		int getMovement();
		void setOriginalHit(Coordinate originalHit);
		Coordinate getOriginalHit();
		std::vector<Ship>* getShips();
		void setManualPlayer();
		bool getManualPlayer();
		void addShips();
		int getRandomNumber(int min, int max);
		set<Coordinate> selectPlaces(int left, int down, set<Coordinate> potentialPlace, int length, int angle);
		void placeShip(Ship* ship, int shipX, int shipY, int posX, int posY, int length, char code, int angle);
		int checkWhichShip(Coordinate coOrds, string playerName);
		void testSinkShip(string playerName);
};