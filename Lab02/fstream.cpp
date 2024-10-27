//filestream examplse (fstream)

//The following program attempts to open a text file called inputfile.txt. If the file exists 
//then the program prints out each line of the file, otherwise it prints an error.

#include <iostream>
#include <fstream>//The library that contains all the file stream operations
#include <string>

int main(int argc, char** argv) {
    std::string filename {"fstream.cpp"};//The file you want to read from, not too important

    //The ifstream object streams information from the file into the program
    //Essentially, it is the "file object you read stuff from"
    std::ifstream myfile {};//"input file stream"

    //We need to associate the ifstream with a file. You need to "open" the file
    myfile.open(filename);

    //Now we can read from the file. We want to check if the file opens successfully
    //since if the file isn't, the program will just crash.

    if (myfile.is_open()) {//is_open returns a boolean 
        std::string line {};

        //now we can use the getline. Getline needs the place to get the line from, and a place to store it.
        std::getline(myfile,line);
        std::cout << line << std::endl;

        //Calling getline subsequently prints out each line of a file. In other words, without much trouble,
        //we can use a loop. But how do we know how many lines of text there are?
        //In fact, the act of calling getline returns a boolean, returning false when it hits
        //a \d -- the end of file character

        while (std::getline(myfile,line)) std::cout << line << std::endl;

        //Now, just as good practice, we should close the file. This deallocates the memory, to prevemt
        //a memory leak.
        myfile.close();

    }
    else{
        std::cout << "File opening failed." << std::endl;
    }
    return 0;
}