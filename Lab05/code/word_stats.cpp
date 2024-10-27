#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <map>
#include <set>
#include <list>


void clean (std::string & V){
  std::string temp_string;
  for(const auto & el: V){
    if (ispunct(el)) continue;
    else if (isupper(el)) temp_string += tolower(el);
    else temp_string += el;
  }
  V = temp_string;
}

void clean (std::vector<std::string> & V){
  for (auto & str: V){
    clean(str);
  }
}

void print(const std::vector<std::string> & V){
	for (const auto & el: V) std::cout << el << std::endl;
}

void print(const std::list<std::string> & L){
	for (const auto & el: L) std::cout << el << std::endl;
}

void print(const std::set<char> & S){
	for (const auto & el: S) std::cout << el << ' ';
	std::cout << std::endl;
}

void print(const std::map<std::string, unsigned long long>& catalog ){
	for (auto data : catalog) {
		// data.first is the key and data.second is the value stored at the key
		std::cout << data.first << ": " << data.second << std::endl;
	}
}

/*
 * Exercise 1
 * 
 * "recently_seen" computes a list of unique words such that the most recently seen 
 * word appears at the top of the list. All words must be lowercase with no 
 * punctuation when they are used as keys to the map.
 * 
 * After looping through all the words in the input, the function prints out the 
 * most recently seen list.
 */
void recently_seen(std::vector<std::string> const& words) {
	auto cleaned_vector = words;
	clean (cleaned_vector);

	std::list<std::string> recently_seen;

	for (const auto& el: cleaned_vector){
		//First, check if el is already in recently_seen and erase it if it is
		for(auto iter = recently_seen.begin(); iter != recently_seen.end(); iter++){
			if (*iter == el){
				recently_seen.erase(iter);
				break;
			}
		}
		recently_seen.push_front(el);
	}
	print (recently_seen);
}

/*
 * Exercise 2
 * 
 * "punctuation" keeps track of all unique punctuation characters which appeared 
 * in the input vector using a std::set. This includes punctuation in words like
 * apostrophes.
 * 
 * After computing the punctuation set, the function prints out the characters.
 */
void punctuation(std::vector<std::string> const& words) {
	std::set<char> punctuation;

	for (const auto& str: words){
		for (const auto & ch: str) {
			if (ispunct(ch)){
				punctuation.insert(ch);
			} 
		}
	}
	print (punctuation);
}

/*
 * Exercise 3
 * 
 * "frequencies" computes the word frequencies of every unique word in the 
 * vector of input using a std::map. All words must be lowercase with no 
 * punctuation when they are used as keys to the map.
 * 
 * After computing the frequencies, the function prints out the frequency data.
 */
void frequencies(std::vector<std::string> const& words) {
	auto cleaned_vector = words;
	clean (cleaned_vector);
	std::map<std::string, unsigned long long> frequency;

	for(const auto& el: cleaned_vector){
		//Check if the element is already in the map; if it is, add 1 to the value
		auto iter = frequency.find(el);
		if (iter != frequency.end()) (*iter).second++;
		else frequency.insert({el, 1});
	}

	print (frequency);
}

int main() {
	std::vector<std::string> words {};
	std::string word {};

	// build vector from piped input
	while (std::cin >> word) {
		words.push_back(word);
	}

	std::cout << "Exercise 1: Computing most recently seen list\n";
	recently_seen(words);

	std::cout << "\nExercise 2: Computing punctuation set\n";
	punctuation(words);
	
	std::cout << "\nExercise 3: Computing word frequencies\n";
	frequencies(words);
}
