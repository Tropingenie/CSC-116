/* histogram.cpp
   CSC 116 - Fall 2019

   B. Bird - 09/30/2019
   Modified by B. Lyne 10/03/2019
*/

#include <iostream>
#include <string>
#include <vector>

/* A histogram is a table which tracks the frequency
   of elements in a sequence. For example, in the
   string "pineapple", a histogram might be
    'p' : 3
    'i' : 1
    'n' : 1
    'e' : 2
    'a' : 1
    'l' : 1
   The struct below encapsulates one entry in the histogram.
*/

struct histogram_entry{
    char character {'a'};
    int count {0};
};

/* Define a histogram to be a list of histogram entries */
using Histogram = std::vector<histogram_entry>;

/* Given a histogram and a character, search for the entry
   for the provided character. If an entry is found, return it.
   If no entry exists, create one, add it to the histogram (with
   a count of zero) and return it.
*/

histogram_entry& get_entry( Histogram& H, char c){
    histogram_entry entry;

    //Check if H.character == c
    for (auto& entry: H){
        if (entry.character == c) return entry;
    }
    //else, create a new entry
    entry.character = c;
    entry.count = 0;
    H.push_back(entry);
    return H.at(H.size()-1);
}

/* Given a string, compute and return a histogram for its elements */

Histogram compute_histogram( std::string input_string ){
    Histogram H;

    for(auto c:input_string){
        auto& H_entry = get_entry(H,c);
        H_entry.count++;
    }

    return H;
}

/* Print the provided histogram in a tabular format, with one entry
   per row */

void print_histogram( const Histogram& H){
    for (auto el: H){
        std::cout << el.character << " :: " << el.count << std::endl;
    }
}


int main(){

    Histogram H1 = compute_histogram("pineapple");
    std::cout << "Histogram for pineapple" << std::endl;
    print_histogram(H1);
    Histogram H2 = compute_histogram("raspberry");
    std::cout << "Histogram for raspberry" << std::endl;
    print_histogram(H2);
    Histogram H3 = compute_histogram("banana");
    std::cout << "Histogram for banana" << std::endl;
    print_histogram(H3);

    return 0;
}