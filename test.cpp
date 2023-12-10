#include <iostream>
#include <cassert>
#include "board.cpp"
using namespace std;

//TODO:
//Do Battleship.cpp, qwerkle, Connect 4, PIoT to clear clutter from folder


void ship_test();

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
    Ship ship(3, "A", "Ship A");

    // Test getLength()
    assert(ship.getLength() == 3);

    // Test getLetter()
    assert(ship.getLetter() == "A");

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

    //Test the board grid
    std::vector<std::vector<std::string>> grid = board.getGrid();
    std::cout<<"Board"<<std::endl;

    // Iterate through the 2D vector
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    //Test the spots hit grid
    grid = board.getSpotsHit();
    std::cout<<"Spots Hit"<<std::endl;

    // Iterate through the 2D vector
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    std::cout<<grid[2][2]<<std::endl;

    grid[2][2] = "A";
    grid[3][3] = "A";

    // Iterate through the 2D vector
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }


    // Output success message if all assertions passed
    std::cout << "All test cases passed!" << std::endl;
}