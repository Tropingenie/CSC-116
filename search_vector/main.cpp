/*
 * search_vector.cpp
 *
 * By Benjamin Lyne
 * V00914888
 *
*/

#include <iostream>
#include <string>
#include <vector>


//Task: Complete the two functions below (start with string_in_vector)

//split_by_comma(str)
//Given a string containing a sequence of tokens separated
//by commas, return a vector containing each token (without the commas)
//For example, if the input is the string "Raspberry,Pear,Grapefruit",
//The vector will contain the elements "Raspberry", "Pear" and "Grapefruit".
std::vector< std::string > split_by_comma( std::string str ){
    std::vector<std::string> output_vector {};
    std::string word {};
    for (auto i: str){
     if (i == ','){
         output_vector.push_back(word);
         word = "";
     }
     else word += i;
     //Debug:
     std::cout << "Word is " << word << std::endl;
    }//end for each loop
    output_vector.push_back(word);//pushes whatever is in the "word" cache into the vector, otherwise program misses "Lemon"
    return output_vector;
}

//string_in_vector(list, search_str)
//Return true if the provided string search_str is an element of the list, and
//return false otherwise.
bool string_in_vector(std::vector< std::string > list, std::string search_str){
    for (auto i: list) if (i == search_str) return true;
    return false;
}

int main(){
    std::string word {};

    // Part 2
    std::string list_str {};
    list_str = "Raspberry,Pear,Grapefruit,Lemon";
    std::vector<std::string> word_list = split_by_comma(list_str);


    /* Part 1 (comment this out when you start part 2) */
    //std::vector<std::string> word_list {"Raspberry","Pear","Lemon"};
    /* */

    std::cout << "Enter a word: ";
    std::cin >> word;
    if (string_in_vector(word_list,word)){
        std::cout << "The word \"" << word << "\" was found in the vector." << std::endl;
    }else{
        std::cout << "The word \"" << word << "\" was not found." << std::endl;
    }

    return 0;
}