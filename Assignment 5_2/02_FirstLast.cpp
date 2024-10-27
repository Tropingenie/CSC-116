/* 02_FirstLast.cpp

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


    std::cout << "Testing first() and last() with modifications" << std::endl;
    std::cout << "First: " << L.first() << " Last: " << L.last() << std::endl;
    L.first() = "Lime";
    L.last() = "Lemon";
    std::cout << "First: " << L.first() << " Last: " << L.last() << std::endl;

    //Make a const reference to L. The first() and last() operations
    //on this variable will use the const versions of those functions.
    const LinkedList<std::string>& CL = L;
    std::cout << "Testing const first() and last():" << std::endl;
    std::cout << "First: " << CL.first() << " Last: " << CL.last() << std::endl;
    

    std::cout << "Testing first() and last() after list manipulation" << std::endl;
    L.pop_front();
    std::cout << "First: " << L.first() << " Last: " << L.last() << std::endl;
    L.pop_back();
    L.pop_front();
    std::cout << "First: " << L.first() << " Last: " << L.last() << std::endl;
    
    L.pop_back();


    std::cout << "Testing first() and last() on an empty list" << std::endl;
    try {
        auto el = L.first();
        std::cout << "first(): No exception thrown (element was \"" << el << "\"" << std::endl;
    } catch(std::runtime_error e) {
        std::cout << "first(): A runtime_error was thrown." << std::endl;
    } catch(...) {
        std::cout << "first(): An unknown object was thrown." << std::endl;
    }
    try {
        auto el = L.last();
        std::cout << "last(): No exception thrown (element was \"" << el << "\"" << std::endl;
    } catch(std::runtime_error e) {
        std::cout << "last(): A runtime_error was thrown." << std::endl;
    } catch(...) {
        std::cout << "last(): An unknown object was thrown." << std::endl;
    }

    return 0;
}