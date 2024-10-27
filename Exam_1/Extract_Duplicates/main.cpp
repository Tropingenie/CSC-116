/* extract_duplicates.cpp
   CSC 116 - Fall 2019

   B. Bird - 09/30/2019
   Modified by B. Lyne 10/03/2019
*/
#include <iostream>
#include <vector>

/* Exercise:
   Implement the extract_duplicates function below, which takes
   a vector V and returns a new vector containing every element
   of V which appears more than once in V. Each element should appear
   only once in the result vector, and the elements in the result
   vector should appear in the same order as their first appearance
   in V.
*/
std::vector<float> extract_duplicates( std::vector<float>& V ){
    std::vector<float> nodup_V;
    bool in_V {false};
    nodup_V.push_back(V.at(0));//otherwise my for loop will yeet itsself

    for(auto el: V){
     //check if el is already in V
        for (auto el2: nodup_V){
            if (el == el2) in_V = true;//if the element being pushed is already in nodup_V, set the flag
        }

        if (in_V) in_V = false;//reset the flag and do nothing
        else nodup_V.push_back (el);//only pushes back el if el isn't in nodup_V already
    }

    return nodup_V;
}



void print_vector( std::vector<float> V ){
    using std::cout;
    using std::endl;

    for(auto x: V)
        cout << x << " ";
    cout << endl;
}

int main(){
    std::vector<float> test_vector {6, 10, 17, 10, -5, 6, 6, 187};

    std::cout << "Before: ";
    print_vector(test_vector);

    auto result = extract_duplicates(test_vector);

    std::cout << "After: ";
    print_vector(result);

    return 0;
}