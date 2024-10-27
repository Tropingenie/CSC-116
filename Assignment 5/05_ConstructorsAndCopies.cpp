/* 05_ConstructorsAndCopies.cpp

   B. Bird - 08/10/2019
*/

#include <iostream>
#include <string>
#include "linkedlist.hpp"

template<typename T>
void pop_and_print( LinkedList<T>& L ){
    while(!L.is_empty()){
        std::cout << L.pop_front() << " ";
    }
    std::cout << std::endl;
}

int main(){

    LinkedList<std::string> L1 {};

    L1.push_back("Grapefruit");
    L1.push_back("Pear");
    L1.push_back("Raspberry");
    L1.push_back("Pineapple");

    //Create a const reference to L1 to ensure that
    //the copy constructor and copy assignment operator
    //are able to correctly work with constant references.
    LinkedList<std::string> const& CL1 = L1;

    
    //Test the copy constructor
    LinkedList<std::string> L2 {CL1};

    //Test the = operator
    LinkedList<std::string> L3 {};
    L3 = CL1;

    //Test the initializer_list constructor
    LinkedList<std::string> L4 {"Grapefruit", "Pear", "Pineapple", "Raspberry"};

    std::cout << "L1: ";
    pop_and_print(L1);
    std::cout << "L2: ";
    pop_and_print(L2);
    std::cout << "L3: ";
    pop_and_print(L3);
    std::cout << "L4: ";
    pop_and_print(L4);

    //Test the chained = operator
    LinkedList<int> L5 {6, 10, 17};
    LinkedList<int> L6 {100, 200, 300};
    LinkedList<int> L7 {1000, 6000, 1700, 1870};

    L5 = L6 = L7;
    std::cout << "L5: ";
    pop_and_print(L5);
    std::cout << "L6: ";
    pop_and_print(L6);
    std::cout << "L7: ";
    pop_and_print(L7);


    return 0;
}