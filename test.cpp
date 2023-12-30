#include <iostream>
#include <cassert>
#include "board.cpp"
using namespace std;

//TODO:
//Do Battleship.cpp, qwerkle, Connect 4, PIoT to clear clutter from folder


void ship_test();
void board_test();

int main() {

	Coordinate coord1(1,2);
	Coordinate coord2(5,7);

	cout << coord1.getX() << " " << coord1.getY() << "\n";
	cout << coord2.getX() << " " << coord2.getY() << "\n";

	ship_test();
}

// Test Ship class methods
void ship_test() {

    // Create a Ship object
    Ship ship(3, 'A', "Ship A");

    // Test getLength()
    assert(ship.getLength() == 3);

    // Test getLetter()
    assert(ship.getLetter() == 'A');

    // Test getName()
    assert(ship.getName() == "Ship A");

    // Test getSunk()
    assert(ship.getSunk() == false);

    // Test addCoordinates()
    ship.addCoordinates(1, 1, 1, 0, 3);

   	// Assuming Coordinate class has correct implementation, 
    // let's assume ship is at (1, 1), (2, 1), (3, 1)

    // Test getCoordinates()
    set<Coordinate> shipCoordinates = ship.getCoordinates();
    assert(shipCoordinates.size() == 3); // Assuming (1, 1), (2, 1), (3, 1)

    // Test addHitSections()
    ship.addHitSections(2, 1); // Assuming hitting the ship at (2, 1)

    // Test getHitSections()
    set<Coordinate> hitSections = ship.getHitSections();
    assert(hitSections.size() == 1); // Assuming (2, 1) has been hit

    // Test checkCoordinates()
    ship.checkCoordinates(1,1,"Player1");
    ship.checkCoordinates(3,1,"Player1");
    assert(ship.checkCoordinates(2, 1, "Player1") == true); // Assuming the ship is now sunk

    // Test sunkShip()
    ship.sunkShip("Player1");
    assert(ship.getSunk() == true);

    Board board("Fred",12);

    //Test get name
    assert(board.getName() == "Fred");
    assert(board.getSize() == 12);
    board.setName("Mike");
    assert(board.getName() == "Mike");

    std::vector<Ship>* shipsPtr = board.getShips();

    for (Ship ship:*shipsPtr) {
        std::cout << ship.getName() << std::endl;
        printf("%s %d %c\n",ship.getName().c_str(),ship.getLength(),ship.getLetter());
    }

    // Output success message if all assertions passed
    std::cout << "All test cases passed!" << std::endl;

    board_test();
}

void board_test() {
    
    //Test case 1: Initialisation and basic getters
    Board board("Test Board", 10);
    assert(board.getName() == "Test Board");
    assert(board.getSize() == 10);

    //Test case 2: Setters and getters for hits
    board.setHitShip(42);
    assert(board.getHitShip()== 42);

    Coordinate hitCoordinate(2,3);
    board.setHit(hitCoordinate);
    assert(board.getHit() == hitCoordinate);

    //Test case 3: Ships-related methods
    board.addShips();
    std::vector<Ship>* ships = board.getShips();
    assert(ships->size()==5);

    for (std::vector<std::string> rows:board.getGrid()) {
        for (std::string cell:rows) {
            std::cout<<cell;
        }
        std::cout<<std::endl;
    }

    //Test case 4: Check ship details
    for(Ship ship:*ships) {
        std::cout << "Ship: " << ship.getName() << " Length: " << ship.getLength() << " Letter: " << ship.getLetter() << std::endl;
    }

    // Test case 5: Board grid and spotsHit
    std::vector<std::vector<std::string>> grid = board.getGrid();
    std::vector<std::vector<std::string>> spotsHit = board.getSpotsHit();
    assert(grid.size() == 10);
    assert(grid[0].size() == 10);
    assert(spotsHit.size() == 10);
    assert(spotsHit[0].size() == 10);

    // Test case 6: Potential shots, ship shots, and manual player
    set<Coordinate> potentialShots;
    potentialShots.insert({1, 1});
    potentialShots.insert({2, 2});
    board.setPotentialShots(potentialShots);
    assert(board.getPotentialShots() == potentialShots);

    set<int> shipShots;
    shipShots.insert(3);
    shipShots.insert(4);
    board.setShipShots(shipShots);
    assert(board.getShipShots() == shipShots);

    board.setManualPlayer();
    assert(board.getManualPlayer() == true);

    board.testSinkShip("Fred");

    std::cout << "All board tests passed" <<std::endl;


}