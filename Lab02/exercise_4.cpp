//Prints a vector of strings in reverse character order (ie, the last character of the last string is printed first)

#include <iostream>
#include <vector>
#include <string>

int main(){

    //Make a vector of all input strings
    std::vector<std::string> all_inputs {};
    std::string current_input {};

    while (std::getline(std::cin,current_input)) all_inputs.push_back(current_input);//takes the input from cin using getline until the command to stop
    //entering input is pressed (ctrl-d on Linux I think)

    //Print each input string in reverse
    for (auto i {all_inputs.size()-1}; i > 0; i--){
        //runs through vector backwards
        current_input = all_inputs.at(i);
        for (auto j {current_input.length()-1}; j > 0; j--) {
            //runs through strings backward
            std::cout << current_input.at(j);
        }
        std::cout << current_input.at(0);
        std::cout << std::endl;
    }

    //The above loop "misses" the string stored at position 0. This covers that case
    current_input = all_inputs.at(0);
        for (auto j {current_input.length()-1}; j > 0; j--) {
            //runs through strings backward
            std::cout << current_input.at(j);
        }
        std::cout << current_input.at(0);
        std::cout << std::endl;


    return 0;
}