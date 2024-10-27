/* 07_RemoveWhere.cpp

   B. Bird - 08/10/2019
*/

#include <iostream>
#include <string>
#include "linkedlist.hpp"

int main(){

    LinkedList<int> L {};

    L.push_back(6);
    L.push_back(10);
    L.push_back(6);
    L.push_back(100);
    L.push_back(10);

    auto print_int = [](int const& i){
        std::cout << i << " ";
    };
    auto is_6 = [](int const& i) -> bool {
        return i == 6;
    };
    std::cout << "Initial list L: ";
    L.apply(print_int);
    std::cout << std::endl;
    
    std::cout << "After removing element 6: ";
    L.remove_where(is_6);
    L.apply(print_int);
    std::cout << std::endl;


    //Now, we will compute all of the prime numbers between 2 and 1000
    //with the Sieve of Eratosthenes
    LinkedList<int> P {};

    //Populate P with every integer from 2 to 1000
    for(int i = 2; i <= 1000; i++){
        P.push_back(i);
    }
    //Now, for each value j between 2 and 1000, remove all multiples
    //of j besides j itself.
    for(int j = 2; j <= 1000; j++){
        auto remove_func = [j](int const& element){
            if (element != j && element%j == 0)
                return true;
            return false;
        };
        P.remove_where(remove_func);
    }


    std::cout << "Primes: ";
    P.apply(print_int);
    std::cout << std::endl;
   

    return 0;
}