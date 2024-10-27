/*
 * vigenere.cpp
 * Version 0.0
 *
 * Benjamin Lyne
 * V00914888
 * Last Compiled On: 14/09/2019
 *
 * Objective: To receive 3 inputs in a specific format, and output an en- and de-coded message based on a simplified
 * Vignere cipher (see file 116f19_assignment1.pdf on connex for specifications of inputs and cipher).
*/

#include <iostream>
#include <string>
#include <cctype>
#include <vector>

std::string encrypt (std::string alphabet, std::string message, std::string key){
/*
 * Encoding:
 *
 * Plan:
 *  Step 1: Number the characters in the alphabet string starting from 0
 *  Step 2: Expand the key to the length of the message
 *  Step 3: Compute numeric indices of letters in both message and key
 *  Step 4: Add the indeces together, wrapping any number above the length of alphabet
 *  Step 5: Convert each index to corresponding character in alphabet table
 */

    std::vector<unsigned int> alphabet_numbering {};

    //Step 1

    for(unsigned int a = 0; a < alphabet.length(); a++){
        alphabet_numbering.push_back(a);
    }

//    //Debug: Prints the "alphabet_numbering" vector
//    std::cout << "Part 1:" << std::endl;
//    for (auto el: alphabet_numbering){
//        std::cout << alphabet_numbering.at(el) << " ";
//    }
//    std::cout << std::endl;

    //Step 2
    unsigned int clock {};
    auto old_key_length {key.length()};

    while (key.length()<message.length()){
        key += key.at(clock);
        clock++;
        if (clock == old_key_length) clock = 0;
    }

//    //debug: Prints the alphabet and the key, so that the lengths can be easily compared
//    std::cout << "Part 2:" << std::endl;
//    std::cout << alphabet <<std::endl;
//    std::cout << message << std::endl;
//    std::cout << key << std::endl;

    //Part 3
    std::vector<unsigned int> index_message {};
    std::vector<unsigned int> index_key {};

    //Compute the Message index
    char letter {};
    unsigned int index {};
    unsigned int message_index {};

    while(index_message.size()!=message.size()){
        index = 0;
        letter = message.at(message_index);
        //look for the value of the letter by counting through the alphabet array
        while (letter != alphabet.at(index)){
            index++;
        }
        index_message.push_back(index);
        message_index++;
    }

    //Compute the Key index (Copied from above; could be made into a function if you wanted to)
    char letter2 {};
    unsigned int key_index {};

    while(index_key.size()!=key.size()){
        index = 0;
        letter2 = key.at(key_index);
        //look for the value of the letter by counting through the alphabet array
        while (letter2 != alphabet.at(index)){
            index++;
        }
        index_key.push_back(index);
        key_index++;
    }

//    //debug: Prints the alphabet and the key, and their indices. Strings are printed with for loops so I individual
//    //characters are easier to identify.
//    std::cout << "Part 3 " << std::endl;
//    std::cout << "Message: " << std::endl;
//    for (auto q: message) std::cout << q << " "; std::cout << std::endl;
//    std::cout << "Message Index: " << std::endl;
//    for (auto q: index_message) std::cout << q << " "; std::cout << std::endl;
//    std::cout << "Key: " << std::endl;
//    for (auto q: key) std::cout << q << " "; std::cout << std::endl;
//    std::cout << "Key Index: " << std::endl;
//    for (auto q: index_key) std::cout << q << " "; std::cout << std::endl;

    //Part 4
    std::vector<unsigned int> index_encoded {};
    unsigned int counter {};
    //Add computed indices of index_message and index_key
    for (auto q: index_message){
        index_encoded.push_back(q+index_key.at(counter));
        counter++;
    }

//    //Debug: Print the index_encoded vector
//    std::cout << "Part 4:" << std::endl;
//    std::cout << "Index Sum: " << std::endl;
//    for (auto q: index_encoded) std::cout << q << " ";
//    std::cout << std::endl;

    //Wrap the indexes to alphabet.length() (this could be done in the above step, but I prefer to implement each
    //"action" separately so as to avoid obfuscation of code)
    counter = 0;
    std::string encrypted {message};//This is just to get encrypted to reserve enough memory to store what's coming
    for (auto q: index_encoded){
        if (q >= alphabet.length()) index_encoded.at(counter) = q - alphabet.length();
        counter++;
    }

//    //Debug: Print the index_encoded vector
//    std::cout << "Wrapped Index Sum: " << std::endl;
//    for (auto q: index_encoded) std::cout << q << " ";
//    std::cout << std::endl;

    //Part 5
    for (clock=0;clock<index_encoded.size();clock++){
        counter = 0;
        //Locate q in the alphabet table
        while (index_encoded.at(clock) != alphabet_numbering.at(counter)){
            counter++;
        }
        encrypted.at(clock) = alphabet.at(counter);
    }
    return encrypted;
}//end encryption function

std::string decrypt (std::string alphabet, std::string message, std::string key){
/*
 * Decoding:
 *
 * Plan:
 *  Step 1-3: Same as last function
 *  Step 4: Compute the difference of the indeces, and wrap the negatives
 *  Step 5: Convert the wrapped indices to the corresponding letters
 *
 *  Below is copied almost verbatim from the encrypt function. The only difference is the difference of index_message
 *  and index_key, and the names of a few variables (eg, encrypted to decrypted) and symbols (eg, < to >).
 */

    std::vector<int> alphabet_numbering {};

    //Step 1

    for(unsigned int a = 0; a < alphabet.length(); a++){
        alphabet_numbering.push_back(a);
    }

//      Debug: Prints the "alphabet_numbering" vector
//    for (auto el: alphabet_numbering){
//        std::cout << alphabet_numbering.at(el) << " ";
//    }
//    std::cout << std::endl;

    //Step 2
    unsigned int clock {};
    auto old_key_length {key.length()};

    while (key.length()<message.length()){
        key += key.at(clock);
        clock++;
        if (clock == old_key_length) clock = 0;
    }
//    //debug: Prints the alphabet and the key, so that the lengths can be easily compared
//    std::cout << alphabet <<std::endl;
//    std::cout << key << std::endl;

    //Part 3
    std::vector<unsigned int> index_message {};
    std::vector<unsigned int> index_key {};

    //Compute the Message index
    char letter {};
    unsigned int index {};
    unsigned int message_index {};

    while(index_message.size()!=message.size()){
        index = 0;
        letter = message.at(message_index);
        //look for the value of the letter by counting through the alphabet array
        while (letter != alphabet.at(index)){
            index++;
        }
        index_message.push_back(index);
        message_index++;
    }

    //Compute the Key index (Copied from above; could be made into a function if you wanted to)
    char letter2 {};
    unsigned int key_index {};

    while(index_key.size()!=key.size()){
        index = 0;
        letter2 = key.at(key_index);
        //look for the value of the letter by counting through the alphabet array
        while (letter2 != alphabet.at(index)){
            index++;
        }
        index_key.push_back(index);
        key_index++;
    }

//    //debug: Prints the alphabet and the key, and their indices. Strings are printed with for loops so I individual
//    //characters are easier to identify.
//    std::cout << "Message: " << std::endl;
//    for (auto q: message) std::cout << q << " "; std::cout << std::endl;
//    std::cout << "Message Index: " << std::endl;
//    for (auto q: index_message) std::cout << q << " "; std::cout << std::endl;
//    std::cout << "Key: " << std::endl;
//    for (auto q: key) std::cout << q << " "; std::cout << std::endl;
//    std::cout << "Key Index: " << std::endl;
//    for (auto q: index_key) std::cout << q << " "; std::cout << std::endl;

    //Part 4
    std::vector<int> index_encoded {};
    unsigned int counter {};
    //Subtract computed indices of index_message and index_key
    for (auto q: index_message){
        index_encoded.push_back(q-index_key.at(counter));
        counter++;
    }

//    //Debug: Print the index_encoded vector
//    std::cout << "Index Sum: " << std::endl;
//    for (auto q: index_encoded) std::cout << q << " ";
//    std::cout << std::endl;

    //Wrap the indexes to above 0 (this could be done in the above step, but I prefer to implement each
    //"action" separately so as to avoid obfuscation of code)
    counter = 0;
    std::string decrypted {message};//This is just to get encrypted to reserve enough memory to store what's coming
    for (auto q: index_encoded){
        if (q < 0) index_encoded.at(counter) = q + alphabet.length();
        counter++;
    }

//    //Debug: Print the index_encoded vector
//    std::cout << "Wrapped Index Sum: " << std::endl;
//    for (auto q: index_encoded) std::cout << q << " ";
//    std::cout << std::endl;

    //Part 5
    for (clock=0;clock<index_encoded.size();clock++){
        counter = 0;
        //Locate q in the alphabet table
        while (index_encoded.at(clock) != alphabet_numbering.at(counter)){
            counter++;
        }
        decrypted.at(clock) = alphabet.at(counter);
    }
    return decrypted;

}//end decrypt function

int main(){
    std::string alphabet {};
    std::string message {};
    std::string key {};

    //Read each of the alphabet, message and key (in that order).
    std::getline(std::cin, alphabet);
    std::getline(std::cin, message);
    std::getline(std::cin, key);

    //Now print out the three input strings in the format specified in the assignment
    std::cout << "Alphabet: [" << alphabet << "]" << std::endl;
    std::cout << "Message: [" << message << "]" << std::endl;
    std::cout << "Key: [" << key << "]" << std::endl;

    std::string encrypted {};
    std::string decrypted {};

    /* Put your solution here, using the strings above to store the encrypted and decrypted results */

    /* ... Your code here ... */
    encrypted = encrypt(alphabet, message, key);
    decrypted = decrypt (alphabet, message, key);

    /* Once both results have been computed, print them out in the format specified in the assignment */
    std::cout << "Encrypted: [" << encrypted << "]" << std::endl;
    std::cout << "Decrypted: [" << decrypted << "]" << std::endl;

    return 0;
}//end main function