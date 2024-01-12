#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

int getNumber(string query,int min, int max);

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