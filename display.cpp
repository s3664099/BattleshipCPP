#include <string>
#include <vector>

//Creates the lines to provide the top and bottom edges of the board
string createLines(string lines) {
	lines = lines+" ";

	for (int x=0;x<12;x++) {
		lines = lines+"-";
	}

	return lines;
}

//Displays the lines
string displayLine(string line, std::vector<std::string> row, string spaces, int x) {

        for (std::string cell:row) {
            line = line+cell;
        }

        line = line+"|";

        return line;
}

//Create a line numbering the columns
string createNumbers(string spaces) {
	string numbers = spaces+"  ";

	for (int x=0;x<10;x++) {
		numbers = numbers+std::to_string(x);
	}

	return numbers;
}

//displays a single grid
void displayGrid(int rows, std::vector<std::vector<std::string>> user) {

	string spaces = "             ";
	string lines = createLines(spaces);
	string numberLine = createNumbers(spaces);

	//Displays the numbers and top line
	std::cout<<numberLine<<std::endl;
	std::cout<<lines<<std::endl;

	int x = 0;

	//Cycles through each of the rows and adds a number and edges
	//displays the rows
	for (std::vector<std::string> rows:user) {
		string line = spaces+std::to_string(x)+"|";
		line = displayLine(line,rows,spaces,x);
		x++;
		std::cout<<line<<std::endl;		
	}

	std::cout<<lines<<std::endl;
}

//Display grids
void displayGrids(int rows, std::vector<std::vector<std::string>> player, std::vector<std::vector<std::string>> computer) {
	string lines = "";
	string spaces = "             ";
	lines = createLines(spaces);
	lines = createLines(lines+spaces);
	string numberLine = createNumbers(spaces)+createNumbers(spaces);
	int x=0;

	std::cout<<numberLine<<std::endl;
	std::cout<<lines<<std::endl;

	//displays the rows
	for (std::vector<std::string> rows:player) {
		string line = spaces+std::to_string(x)+"|";
		line = displayLine(line,rows,spaces,x)+spaces;
		line = line+to_string(x)+"|";
		line = displayLine(line,computer[x],spaces,x);
		x++;
		std::cout<<line<<std::endl;		
	}

	std::cout<<lines<<std::endl;	
}
