#include <iostream>
#include <vector>
#include <string>

int alliteration_count(std::vector<std::string> input_vector){
    int count {};
    std::string input_string {};
    //step 1: concatenate the entire vector as a single string
    for (auto str: input_vector){
        input_string += str;
    } 
    std::cout << input_string << std::endl;

    char alliterated_letter {input_string.at(0)};
    for (auto t {input_string.length}){
        //Look at each letter that comes after a space

    }
    return count;
}

int main (){
    std::string input_string {};
    std::vector<std::string> input_vector {};
    int count {};

    while(std::getline(std::cin,input_string)) input_vector.push_back(input_string);

    count = alliteration_count(input_vector);

    std::cout << "Count ist " << count << std::endl;

    return 0;
}