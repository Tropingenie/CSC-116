/* 04_CompareOperators.cpp

   B. Bird - 08/10/2019
*/

#include <iostream>
#include <string>
#include "linkedlist.hpp"


std::string bool_string(bool b){
    if (b)
        return "true";
    else    
        return "false";
}

int main(){

    LinkedList<int> L1 {};
    LinkedList<int> L2 {};
    LinkedList<int> L3 {};
    LinkedList<int> L4 {};
    LinkedList<int> L5 {};

    L1.push_back(6);
    L1.push_back(10);
    L1.push_back(17);

    L2.push_back(6);
    L2.push_back(10);
    L2.push_back(17);
    L2.push_back(187);

    L3.push_back(6);
    L3.push_back(10);
    L3.push_back(17);
    L3.push_back(187);

    L4.push_back(10);
    L4.push_back(6);
    L4.push_back(187);
    L4.push_back(17);

    std::cout << "L1 == L1: " << bool_string(L1 == L1) << std::endl;
    std::cout << "L1 != L1: " << bool_string(L1 != L1) << std::endl;

    std::cout << "L1 == L2: " << bool_string(L1 == L2) << std::endl;
    std::cout << "L1 != L2: " << bool_string(L1 != L2) << std::endl;

    std::cout << "L2 == L1: " << bool_string(L2 == L1) << std::endl;
    std::cout << "L2 != L1: " << bool_string(L2 != L1) << std::endl;

    std::cout << "L2 == L3: " << bool_string(L2 == L3) << std::endl;
    std::cout << "L2 != L3: " << bool_string(L2 != L3) << std::endl;

    std::cout << "L3 == L2: " << bool_string(L3 == L2) << std::endl;
    std::cout << "L3 != L2: " << bool_string(L3 != L2) << std::endl;

    std::cout << "L3 == L4: " << bool_string(L3 == L4) << std::endl;
    std::cout << "L3 != L4: " << bool_string(L3 != L4) << std::endl;

    std::cout << "L4 == L3: " << bool_string(L4 == L3) << std::endl;
    std::cout << "L4 != L3: " << bool_string(L4 != L3) << std::endl;

    std::cout << "L4 == L5: " << bool_string(L4 == L5) << std::endl;
    std::cout << "L4 != L5: " << bool_string(L4 != L5) << std::endl;

    std::cout << "L5 == L4: " << bool_string(L5 == L4) << std::endl;
    std::cout << "L5 != L4: " << bool_string(L5 != L4) << std::endl;

    //Verify that the operators continue to work even if the underlying lists
    //are constant..
    LinkedList<int> const& CL1 = L1;
    LinkedList<int> const& CL2 = L2;

    std::cout << "CL1 == CL1: " << bool_string(CL1 == CL1) << std::endl;
    std::cout << "CL1 != CL1: " << bool_string(CL1 != CL1) << std::endl;

    std::cout << "CL1 == CL2: " << bool_string(CL1 == CL2) << std::endl;
    std::cout << "CL1 != CL2: " << bool_string(CL1 != CL2) << std::endl;


    return 0;
}