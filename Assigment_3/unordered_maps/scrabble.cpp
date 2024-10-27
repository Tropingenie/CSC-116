/* scrabble.cpp
   CSC 116 - Fall 2019

   Complete the implementations of each of the functions below (declared in scrabble.hpp)

   Benjamin Lyne, V00914888 - 10/25/2019
*/

#include <iostream>
#include <set>
#include "scrabble.hpp"



/* Member functions */
ScrabbleSolver::ScrabbleSolver(){}//Trivial default constructor

    /* add_word(word)
       Add the provided word to the internal dictionary of this solver.
       If the word is already present in the dictionary, throw an
       exception of type std::runtime_error.
    */
void ScrabbleSolver::add_word( std::string const& word ){
    if(dictionary_map.find(word) != dictionary_map.end()) throw std::runtime_error("Error: Word (\"" + word +"\") already in dictionary");
    else{
        dictionary_map.insert(std::make_pair( word,compute_score(word) ));
    }
}

    /* get_score_map()
       Return a map containing all words in the dictionary, mapped to their
       scores (as computed by compute_score).

       dont use this its so hecking inefficient lol. The variable of type std::map named "dictionary_map" does
       the same thing as the function below by automatically calculating the scores of the words as they are added
       by the add_word() function-- B. Lyne
    */
ScoreMap ScrabbleSolver::get_score_map(){
    ScoreMap map;
    for (auto pair: dictionary_map){
        map.insert(pair);
    }
    return map;
}

/* find_words(tiles)
   Given a set of tiles, return a map containing all possible
   words that can be created from the provided tiles, with each word
   word is mapped to its score.

   Remember that it is not necessary for a word to use all of the provided
   tiles (some tiles may be left unused).

   Hint: Try using get_score_map first
*/
ScoreMap ScrabbleSolver::find_words( TileSet const& tiles ){
    ScoreMap output {};

    //Search through the map of dictionary words (and their scores) to find every word
    //that can be made using the tiles given (using the can_make_word() function)
    //Insert the element of every word that can be made.
    for (const auto & mapped_word: dictionary_map){
        const auto& word = mapped_word.first;
        if ( can_make_word(word, tiles) ) output.insert(mapped_word);
    }
    return output;
}

/* find_best_words(tiles)
   Given a set of tiles, return a map containing only the highest-scoring
   words that can be created from the provided tiles, with each word
   mapped to its score.

   Remember that it is not necessary for a word to use all of the provided
   tiles (some tiles may be left unused).

   Hint: Use find_words first.
*/
ScoreMap ScrabbleSolver::find_best_words( TileSet const& tiles ){//TileSet is of type std::set<string>
    auto words = find_words(tiles);
    int best_word_score {0};
    ScoreMap best_words;//ScoreMap is the type std::map<string,int>
    //Determine the highest score
    for (const auto & pair: words){
        const auto & score = pair.second;
        if (score > best_word_score) best_word_score = score;
    }
    //Insert every word with the highest score into the best_words map
    for (const auto & pair: words){
        const auto & score = pair.second;
        if (score == best_word_score) best_words.insert(pair);
    }
    return best_words;
}

/* Static member functions */


    /* compute_score(word)
       Compute and return the score of the provided word.
    */
int ScrabbleSolver::compute_score( std::string const& word ){
    int score{0};
    for (auto ch: word) score += letter_score(ch);
    return score;
}

    /* can_make_word(word, tiles)
       Return true if the provided word can be constructed using the provided
       tiles and false otherwise.
    */
bool ScrabbleSolver::can_make_word( std::string const& word, TileSet const& tiles ){
    std::map<char, int> instances {};
    //Calculate every letter instance in specified word
    for (const auto & ch: word){
        instances[ch]++;
    }
    //Then remove the letters in the tileset
    for (const auto & ch: tiles){
        instances[ch]--;
    }
    //If any of the mapped values are > 0, then you don't have enough tiles to make the word
    for (const auto & el: instances){
        if (el.second > 0) return false;
    }
    return true;
}