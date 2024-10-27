/* 06_Apply.cpp

   B. Bird - 08/10/2019
*/

#include <iostream>
#include <string>
#include "linkedlist.hpp"

int main(){

    LinkedList<int> Li {6, 10, 17, 187, 116, 225};
    const LinkedList<int>& Lci = Li;

    LinkedList<std::string> Ls { "C", "C++", "Java", "Python" };

    auto print_int = [](int const& i){
        std::cout << i << " ";
    };
    std::cout << "Printing list (twice)." << std::endl;
    Li.apply(print_int);
    std::cout << std::endl;
    Lci.apply(print_int);
    std::cout << std::endl;

    std::cout << std::endl;

    auto add_1000 = [](int& i){
        i = i + 1000;
    };
    std::cout << "Adding 1000 to each element." << std::endl;
    Li.apply(add_1000);
    Lci.apply(print_int);
    std::cout << std::endl;


    std::cout << "Concatenating elements." << std::endl;
    std::string result = "";
    auto concatenate_strings = [&result](std::string const& s){
        result += s + " ";
    };
    Ls.apply(concatenate_strings);
    std::cout << "Result: " << result << std::endl;
    return 0;
}