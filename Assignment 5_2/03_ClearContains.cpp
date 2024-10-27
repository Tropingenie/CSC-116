/* 03_ClearContains.cpp

   B. Bird - 08/10/2019
*/

#include <iostream>
#include <string>
#include "linkedlist.hpp"

void test_contains(LinkedList<std::string>& L, const std::string& element){
    if (L.contains(element)){
        std::cout << "L contains \"" << element << "\"" << std::endl;
    }else{
        std::cout << "L does not contain \"" << element << "\"" << std::endl;
    }
}

int main(){

    LinkedList<std::string> L {};

    L.push_back("Grapefruit");
    L.push_back("Pear");
    L.push_back("Raspberry");
    L.push_back("Pineapple");
    L.push_front("Lemon");
    L.push_front("Lime");
    L.push_front("Peach");
    L.push_front("Orange");

    std::cout << "Part 1" << std::endl;
    test_contains(L, "Raspberry");
    test_contains(L, "Grapefruit");
    test_contains(L, "Orange");
    test_contains(L, "Pomegranate");

    std::cout << std::endl;
    std::cout << "Part 2" << std::endl;
    L.pop_front();
    L.pop_back();
    test_contains(L, "Raspberry");
    test_contains(L, "Grapefruit");
    test_contains(L, "Orange");

    std::cout << std::endl;
    std::cout << "Part 3" << std::endl;
    L.clear();
    test_contains(L, "Raspberry");
    test_contains(L, "Grapefruit");
    test_contains(L, "Orange");

    std::cout << std::endl;
    std::cout << "Part 4" << std::endl;
    L.push_back("Apple");
    test_contains(L, "Apple");


    return 0;
}