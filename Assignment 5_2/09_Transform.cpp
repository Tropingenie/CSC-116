/* 08_Transform.cpp

   B. Bird - 08/10/2019
*/

#include <iostream>
#include <string>
#include "linkedlist.hpp"

int main(){

    LinkedList<std::string> L {};

    L.push_back("Grapefruit");
    L.push_back("Pear");
    L.push_back("Raspberry");
    L.push_back("Pineapple");

    auto print_string = [](std::string const& s){
        std::cout << s << " ";
    };
    auto print_unsigned_int = [](unsigned int const& i){
        std::cout << i << " ";
    };

    auto str_to_size = [](std::string const& s) -> unsigned int{
        return s.length();
    };

    std::cout << "L: ";
    L.apply(print_string);
    std::cout << std::endl;


    auto L_sizes = L.transform<unsigned int>(str_to_size);
    std::cout << "L_sizes: ";
    L_sizes.apply(print_unsigned_int);
    std::cout << std::endl;


    auto str_to_first_char = [](std::string const& s) -> std::string{
        std::string result {};
        result += s.at(0);
        return result;
    };
    auto L_first_char = L.transform<std::string>(str_to_first_char);
    std::cout << "L_first_char: ";
    L_first_char.apply(print_string);
    std::cout << std::endl;

    return 0;
}