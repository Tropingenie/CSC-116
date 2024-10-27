/* 06_DeepCopy.cpp

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

    
    LinkedList<std::string> L2(L1);
    LinkedList<std::string> L3 {};
    L3 = L1;

    L1.push_back("Peach");
    L2.push_back("Apple");
    L3.push_back("Orange");

    std::cout << "L1: ";
    pop_and_print(L1);
    std::cout << "L2: ";
    pop_and_print(L2);
    std::cout << "L3: ";
    pop_and_print(L3);


    return 0;
}