#include <iostream>
#include <fstream>
#include <string>

/*
Modify this previous program so that the name of the input file is given by the 
first command line argument. Create a text file called seashells.txt and copy-paste 
the [given] text. Be sure you save seashells.txt in the same directory as the 
your source code.
*/


int main(int argc, char** argv) {

    std::string filename {argv[1]};
    std::ifstream myfile {};
    myfile.open(filename);
    
    if (myfile.is_open()) {
        std::string line {};
		
        while (std::getline(myfile, line)) {
            std::cout << line << std::endl;
        }
        myfile.close();
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
	
    return 0;
}