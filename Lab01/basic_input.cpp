/*
*   basic_input.cpp
*   Benjamin Lyne
*   Sept. 12 2019
*   Demonstrates understanding of std::cout and std::cin and how they can be used.
*   Takes numeric input from user until an invalid input is received, then prints 
*   an error message, sum of all the imputs, and a count of how many valid inputs
*   were received.
*/

#include <iostream>

int main() {

	float num {};
	float sum {};
    unsigned int counter {};

	std::cout << "Enter a number: ";
    
	while (std::cin >> num){
        std::cout << "Enter a number: ";
        counter++;
        sum+=num;
    }
	
	std::cout << "Input was invalid; terminating code" << std::endl;
	std::cout << "Number of valid values entered:" << counter << std::endl;
	std::cout << "Sum:" << sum << std::endl;

	return 0;
}