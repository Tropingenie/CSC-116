/*
*   basic_input.cpp
*   Benjamin Lyne
*   Sept. 12 2019
*   Demonstrates understanding of vectors and how they can be used.
*   Takes numeric input from user until an invalid input is received, then prints 
*   an error message, number of elements read, and the elements in reverse order of input.
*/

#include <iostream>
#include <vector>

int main() {

	float num {};
	std::vector<float> numbers {};
    unsigned int counter {};

	std::cout << "Enter a number: ";
    
	while (std::cin >> num){
        std::cout << "Enter a number: ";
        counter++;
        numbers.push_back(num);
    }
	
	std::cout << "Input was invalid; terminating code" << std::endl;
	std::cout << "Number of valid values entered:" << counter << std::endl;
	std::cout << "Values (forward): ";

    for (auto con: numbers){
        std::cout << con << " ";
    }
    std::cout << std::endl;

    std::cout << "Values (reverse): ";
    for (unsigned  int q = numbers.size(); q > 0; q--){
        std::cout << numbers.at(q-1);
        std::cout << " ";
    }
    std::cout << std::endl;

	return 0;
}