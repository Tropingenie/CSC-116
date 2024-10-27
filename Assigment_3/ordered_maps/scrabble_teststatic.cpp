/* scrabble_teststatic.cpp

   A program to test the static methods in the ScrabbleSolver class (to make it
   easier to start with the static functions before implementing the class methods).

   To use this tester, compile with
     g++ -pedantic -Wall -Wextra -std=c++17 -o scrabble_teststatic scrabble.cpp scrabble_teststatic.cpp
   then run with the command
     scrabble_teststatic tiles word

   For example,
     scrabble_teststatic eeaarrp pear

   B. Bird - 08/03/2019
*/

#include <iostream>
#include <string>
#include "scrabble.hpp"



int main(int argc, char** argv){
    if (argc < 3){
        std::cout << "Usage: " << argv[0] << " tiles word" << std::endl;
        return 1;
    }
    std::string tiles = argv[1];
    std::string word = argv[2];
    std::cout << "Provided tiles: [" << tiles << "]" << std::endl;
    std::cout << "Target word: [" << word << "]: Score = " << ScrabbleSolver::compute_score(word) << std::endl;
    auto tile_set = ScrabbleSolver::string_to_tileset(tiles);
    if (ScrabbleSolver::can_make_word(word, tile_set)){
        std::cout << "can_make_word returned true: The word " << word << " can be created from the provided tiles." << std::endl;
    }else{
        std::cout << "can_make_word returned false: The word " << word << " cannot be created from the provided tiles." << std::endl;
    }


    return 0;
}