/* capitalize_each_word.cpp
   CSC 116 - Fall 2019

   B. Bird - 09/30/2019
   Modified by B. Lyne - 10/03/2019
*/
#include <iostream>
#include <string>
#include <cctype>

/* Exercise:
   Implement the capitalize_each_word function below, which takes
   a string s and returns a new string resulting from capitalizing
   the first letter of each word of s. You may assume that the input
   string will consist of sequences of letters (uppercase or lowercase)
   separated by one or more spaces. No hyphens or punctuation will
   be present.

   The std::toupper(c) function in the cctype library takes a char value c
   and returns its uppercase representation.
*/
std::string capitalize_each_word( const std::string& s ){
    auto capitalised_string = s;
    bool previous_c_was_space {false};

    if (capitalised_string.at(0) != ' ')
        capitalised_string.at(0) = toupper(capitalised_string.at(0));//Capitalises the first letter if it is one

    for(char& c: capitalised_string){
        if (c == ' ') previous_c_was_space = true;
        else if (previous_c_was_space){//runs only if (c != ' ')
            c = std::toupper(c);
            previous_c_was_space = false;//reset the flag
        }
        //Otherwise nothing happens.
    }

    return capitalised_string;
}


int main(){
    std::string input_string {"here    are    SOME words"};

    std::cout << "Before: " << input_string << std::endl;

    auto result = capitalize_each_word(input_string);

    std::cout << "After: " << result << std::endl;

    return 0;
}