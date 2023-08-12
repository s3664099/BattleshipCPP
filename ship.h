#include <string>
#include <set>
#include "coordinate.cpp"

class Ship {
	
	private:
		int length;
		string letter;
		string name;
		bool sunk;
		set <Coordinate> hitSections;
		set <Coordinate> coordinates;

	public:
		Ship(int length, string letter, string name);
		int getLength();
		string getLetter();
		string getName();
		bool getSunk();
		void addCoordinates(int xCoord, int yCoord, int incX, int incY, int length);
		void addHitSections(int xCoord, int yCoord);
		set<Coordinate> getHitSections();
		bool checkCoordinates(int xCoord,int yCoord, string playername);
		void sunkShip(string playername);
		set<Coordinate> getCoordinate();

}