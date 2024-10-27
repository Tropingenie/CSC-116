#include <iostream>
#include <vector>
#include <cmath>
#include <exception>

using exception = std::string;//I wrote this before we did the lecture on exception types, sorry.
using ull = unsigned long long;//I'm lazy and OCD -- clang-tidy was bugging me to use unsigned long long ints.
/* DO NOT MODIFY ANY CODE BETWEEN THIS LINE AND main() */
using Matrix = std::vector< std::vector< double > >;


/* read_matrix()
   Attempt to read a matrix (in the format described in the assignment specification)
   from standard input. If a matrix is read successfully, it will be returned. If
   any kind of read error occurs, the function will throw an instance of std::runtime_error.
*/
Matrix read_matrix(){
    int rows, cols;
    std::cin >> rows;
    if (!std::cin)
        throw std::runtime_error("Unable to read number of rows");

    std::cin >> cols;
    if (!std::cin)
        throw std::runtime_error("Unable to read number of columns");

    Matrix result {};
    //Now read each row and add it to the matrix
    for(int i = 0; i < rows; i++){
        std::vector<double> row {};
        for (int j = 0; j < cols; j++){
            double entry;
            std::cin >> entry;
            if (!std::cin){
                throw std::runtime_error("Unable to read entry "+std::to_string(i)+","+std::to_string(j));
            }
            row.push_back(entry);
        }
        result.push_back(row);
    }
    return result;
}

/* PUT YOUR SOLUTION BELOW THIS LINE */
/* You may add extra functions if necessary */
void print(const Matrix& A){//prints a matrix
    //Debug function used to print the matrix
    std::cout << "The matrix is:" << std::endl;
    for (const auto& i: A){
        for (const auto& j: i){
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

void print(const std::vector<double>& x){
    for (auto el: x) std::cout << el << std::endl;
}



int main() {
    Matrix A = read_matrix();
    for (ull i = 0; i < A.size(); i++){
        std::cout << "i is " << i << std::endl;
        ull q = find_largest_row_index(A,i);
        std::cout << "Found largest row index of column i. q = " << q << std::endl;
        print(A); std::cout << std::endl;
        swap_rows(A, i, q);
        std::cout << "Swapped rows i and q." << std::endl;
        print(A); std::cout << std::endl;
    }
    return 0;
}