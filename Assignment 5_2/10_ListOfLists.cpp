/* 10_ListOfLists.cpp

   B. Bird - 11/19/2019
*/

#include <iostream>
#include <string>
#include "linkedlist.hpp"

int main()
{
    LinkedList< LinkedList<std::string> > L{};
    
    LinkedList< std::string > L1 {"Lemon","Lime"};
    LinkedList< std::string > L2 {"Raspberry", "Pear", "Banana"};

    L.push_back(L1);
    L.push_back(L2);
    L1.push_back("Orange");
    L1.push_back("Apple");
    L.push_back(L1);


    auto print_element = [](std::string const& el){
        std::cout << el << " ";
    };

    auto print_sublist = [print_element](LinkedList< std::string > const& sublist ){
        std::cout << "  Sublist: ";
        sublist.apply(print_element);
        std::cout << std::endl;
    };

    std::cout << "Printing Nested Lists:" << std::endl;
    L.apply(print_sublist);

    std::cout << std::endl;

    auto get_last = [](LinkedList<std::string> const& sublist){
        return sublist.last();
    };
    std::cout << "Extracting last elements: ";
    auto new_L = L.transform<std::string>(get_last);
    new_L.apply(print_element);
    std::cout << std::endl;

    return 0;
}
