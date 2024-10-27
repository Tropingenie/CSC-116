//Demonstrates std::getline and printing an std::vector in reverse order

#include <iostream>
#include <vector>
#include <string>

//Prints input lines in reverse order

int main(){

    std::vector<std::string> all_inputs {};
    std::string current_input {};

    while (std::getline(std::cin,current_input)) all_inputs.push_back(current_input);

    for (auto i {all_inputs.size()-1}; i > 0; i--) std::cout << all_inputs.at(i) <<std::endl;
    std::cout << all_inputs.at(0) <<std::endl;
    return 0;
}