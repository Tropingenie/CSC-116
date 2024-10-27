
/* read_grades.cpp
   CSC 116 - Fall 2019 - Lab 3
*/
#include <iostream>
#include <vector>
#include <algorithm>

/* compute_mean(V)
 * Given a vector V containing ints, return the average
 * of all elements in V. (Note that the average will be a
 * float, not an int).
 * If the vector V contains no elements, the result must be 0.
 */
float compute_mean(std::vector<int> const &V) {
    float mean {0};
    for (auto i: V){
        mean += i;
    }
    if (V.size()!=0) mean/=V.size();
    /* your code here */
    return mean;
}

/* compute_median(V)
 * Given a vector V containing ints, return the median of all
 * elements in V.
 *
 * Recall that the median of a sequence is the value that
 * would appear in the "middle" of the sorted version of the sequence.
 * If the sequence has an odd number of elements, the median
 * will be the single value in the middle. If the sequence
 * has an even number of elements, the median will be the
 * average of the two values in the middle.
 *
 * For example, the median of the sequence {3, 6, 2, 1, 0} is 2,
 * and the median of the sequence {7, 9, 2, 3, 1, 4} is 3.5.
 *
 * If the vector V contains no elements, the result must be 0.
 */
float compute_median(std::vector<int> const &V) {
    /* your code here */
    float median{0};
    bool even {false};
    if (V.size()%2==0) even = true;


    std::vector<int> V_sorted{V};
    std::sort(V_sorted.begin(),V_sorted.end());//std::sort sorts a vector in order of size
    //I think that it's from smallest to largest

    if (even){
        //Take the average of the two middle numbers
        int V_middle {V.size()};
        V_middle /= 2;
        median = V_sorted.at(V_middle-1)+V_sorted.at(V_middle);
        median /= 2;
        //Example of the above code for a 4-long vector:
        //median = V.at(2)+V.at(1)
    }
    else{
        //Take the middle number
        int middle_address {V_sorted.size()/2}; //This should round down to the middle number
        //since ints always "round" down.
        median = V_sorted.at(middle_address);
    }
    return median;
}

/* delete_zeros(V)
 * Given a vector V containing ints, delete all
 * zero values from V.
 */
void delete_zeros(std::vector<int> &V) {
    std::vector<int> output {};
    for (auto i: V){
        if (i == 0);//do nothing
        else output.push_back(i);
    }
    V = output;
    /* hint: create a new vector and push_back non-zero elements */
}

/* print_vector(V)
 * Print the elements of the vector V, does 
 * not print a new line
 */
void print_vector(std::vector<int> const &V) {
    for(auto x : V) {
        std::cout << x << ' ';
    }
}

int main() {
    
    // Read in grades and push_back into vector
    std::vector<int> grades{};
    int n{};
    while(std::cin >> n) {
        grades.push_back(n);
    }

    std::cout << "Read " << grades.size() << " grades" << std::endl;
    std::cout << "Original grades: ";
    print_vector(grades);
    std::cout << std::endl;

    std::cout << "Average: " << compute_mean(grades) << std::endl;
    std::cout << "Median: " << compute_median(grades) << std::endl;

    // Delete all of the zero grades from the vector
    delete_zeros(grades);

    std::cout << "Grades with zeros removed: ";
    print_vector(grades);
    std::cout << std::endl;

    std::cout << "Average (zeros excluded): " << compute_mean(grades) << std::endl;
    std::cout << "Median (zeros excluded): " << compute_median(grades) << std::endl;

    return 0;
}