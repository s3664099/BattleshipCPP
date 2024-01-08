#include <string>
#include <vector>

//Creates the lines to provide the top and bottom edges of the board
string createLines(string line) {
	lines = lines+" ";

	for (int x=0;x<12;x++) {
		lines = lines+"-";
	}

	return lines;
}

//Displays the lines
string displayLine(string line, std::vector<std::string> row, string spaces, int x) {

        for (std::string cell:rows) {
            line = line+cell;
        }

        line = line+"|";

        return line;
}

string createNumbers(string spaces) {
	string numbers = spaces+" ";

	for (int x=0;x<10;x++) {
		numbers = numbers+x;
	}

	return numbers;
}
