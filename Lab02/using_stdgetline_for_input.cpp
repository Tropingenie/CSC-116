//getline as input

#include <string>
#include <fstream>
#include <iostream>

int main(){

    std::string input {};
  //recall: getline takes an input and an output location, and is used as a boolean.
    while(std::getline(std::cin, input)) std::cout << "Input: " << input <<std::endl;
}