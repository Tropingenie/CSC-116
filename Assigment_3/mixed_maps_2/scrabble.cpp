/* scrabble.cpp
   CSC 116 - Fall 2019

   Complete the implementations of each of the functions below (declared in scrabble.hpp)

   Objective: Computes various useful numbers for the game Scrabble. See comments above each member and static function
   for more specifics on what is calculated.

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

//I deleted get_score_map because it was hella inefficient to compute the scoremap every time it was needed.
//Instead, "dictionary" is stored internally as an unordered score map.

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
    ScoreMap words;//Use a map here to save registers (since umap uses hash tables and isn't much faster from my testing)
    //First, compute all the possible words. I could use the function find_words() here, but that is passing by value
    //and thus introducing inefficiency--instead, I will just copy and modify the code for find_words() here.
    for (const auto & mapped_word: dictionary_map){
        const auto& word = mapped_word.first;
        if ( can_make_word(word, tiles) ) words.insert(mapped_word);
    }
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
    //Since supposedly maps have slightly faster insert times, I don't use an unordered one here.
    const std::map<char,int> letter_scores {
        {'a', 1},{'e', 1},{'i', 1},{'l', 1},{'n', 1},{'o', 1},{'r', 1},{'s', 1},{'t', 1},{'u', 1},
        {'d', 2},{'g', 2},
        {'b', 3},{'c', 3},{'m', 3},{'p', 3},
        {'f', 4},{'h', 4},{'v', 4},{'w', 4},{'y', 4},
        {'k', 5},
        {'j', 8},{'x', 8},
        {'q', 10},{'z', 10}
    };
    for (auto ch: word) score += letter_scores.at(ch);//[] weren't working for whatever reason
    return score;
}

    /* can_make_word(word, tiles)
       Return true if the provided word can be constructed using the provided
       tiles and false otherwise.
    */
bool ScrabbleSolver::can_make_word( std::string const& word, TileSet const& tiles ){
    //We cannot just check if each letter is in the multiset, since letters could appear multiple times. Thus, the
    //following is a fairly elegant (though, I cannot say how efficient) solution. -B.Lyne

    std::unordered_map<char, int> instances {};//Unordered maps are supposedly faster
    //Calculate every letter instance in specified word
    for (const auto & ch: word){
        instances[ch]++;//because of the square brackets, will add new elements to the map if they don't exist yet
    }
    //Then remove the letters in the tileset
    for (const auto & ch: tiles){
        instances[ch]--;
    }
    //If any of the mapped values are > 0, then you don't have enough tiles to make the word
    for (const auto & el: instances){
        if (el.second > 0) return false;
    }
    //else:
    return true;
}