#include <iostream>
using namespace std;

int main() {

	Coordinate coord1(1,2);
	Coordinate coord2(5,7);

	cout << coord1.getX() << " " << coord1.getY() << "\n";
	cout << coord2.getX() << " " << coord2.getY() << "\n";
}