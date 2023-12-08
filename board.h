#include <string>
#include <set>
#include <vector>
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
		set <Ship> ships;
		int hitShip;
		Coordinate hit;
		Coordinate originalHit;
		int movement;
		bool manualPlayer;
		string[][] addShip(Ship ship);
		Ship checkShipHit(Coordinate coOrds, string playerName);
		void removeShip(Ship shipToRemove);
		bool checkRemainingShips();
		void markGrid(set<Coordinate> sectionsToMark);

	public:
		Board(string objectName, int size);
		string getName();
		int getSize();
		void setName(string objectName);
		string[][] getGrid();
		string[][] getSpotsHit();
		set<Coordinate> getPotentialShots();
		void setPotentialShots(set<Coordinate> potentialShots);
		set<int> getShipShots();
		void setShipShots(set<Integer> shipShots);
		void setHitShip(int hitShip);
		int getHitShip();
		void setHit(Coordinate hit);
		Coordinate getHit();
		void setMovement(int movement);
		int getMovement();
		void setOriginalHit(Coordinate originalHit);
		Coordinate getOriginalHit();
		set<Ship> getShips();
		void setManualPlayer();
		bool getManualPlayer();
		void addShips();
		int getRandomNumber(int min, int max);
		set<Coordinate> selectPlaces(int left, int down, set<Coordinate> potentialPlace, int length, int angle);
		string[][] placeShip(Ship ship, int shipX, int shipY, int posX, int posY, int length, string code, int angle);
		int checkWhichShip(Coordinate coOrds, string playerName);
		void testSinkShip(string playerName);
};