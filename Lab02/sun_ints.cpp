#include <iostream>
#include <vector>
#include <string>


//argc and argv are set by the compiler or terminal, since they are arguments of main
//But what exactly are they? They aren't in global scope, so they're not global variables...

int main (int argc, char** argv){

//char** argv is a C styled array of strings. These are the parameters you pass into the
//program (through the terminal).

//int argc is the number of parameters passed into main

//since we have a c-styled array, we'll convert it into a vector
    std::vector<std::string> argument {};//vector.push_back automatically converts c strings into std::string
    for (int i {1}; i < argc; i++){//note that, since we only want the arguments following the execution, we start the counter at 1 instead of 0
        argument.push_back(argv[i]);
    }

//Now, using our vector of strings, let's print out what argc is

    std::cout << argc << std::endl;
    //After testing, we found that argc was one larger than the amount of arguments we typed...
/*

blyne5658@u-devil:~/CSC 116/Lab02$ ./sun_ints 1 2 3
4

*/
    //Or did it? What if ./sun_ints counts as an argument? In fact, it does, so there are indeed 4 arguments.

//Anyways, we now need to convert our strings into ints, and summate them
    int sum{};
    for (auto arg: arguments){
        sum += std::stoi(arg);
    }

    return 0;    
}