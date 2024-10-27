/* gauss.cpp
   CSC 116 - Fall 2019 - Assignment 2

   Benjamin Lyne
   V00914888
   Last Compiled On: 2019-10-04

   Task: Row reduce an augmented matrix using Gaussian Elimination and Back Substitution. Return vector "x" for Ax=b.
*/

#include <vector>
#include <iostream>
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

inline void print(const std::vector<double>& vec){
    for(const auto & el: vec) std::cout << el << std::endl;
}

void swap_rows(Matrix &M, ull i, ull q){//swaps row i with row q
//    std::cout << "swap_rows" << std::endl;
    auto store_row {M.at(i)};
    M.at(i) = M.at(q);
    M.at(q) = store_row;
}

ull find_largest_row_index(const Matrix& M, ull i){
    //Find the index q ∈ {i, i + 1, . . . , n − 1} of the row with the largest value of |Aqi|.

    double EGM {0};//EGM means "Element of Greatest Magnitude"
    ull EGM_row_index;
    ull q = i;

    for(;q < M.size();q++){
        auto Aqi = M.at(q).at(i);
        if (fabs(Aqi) > EGM){
            EGM = fabs(Aqi);
            EGM_row_index = q;
        }
    }

    //std::cout << "EGM_row_index is " << EGM_row_index << std::endl;
    return EGM_row_index;
}

void reduce_one_row(Matrix& M, ull i){//Subtracts (Ari/Aii)*row_i - row_r
//    std::cout << "Entered reduce_one_row function" << std::endl;

/*
 * The specification asks for the following:
 * For r = i + 1, i + 2, . . . , n − 1
 *  ∗ Subtract (Ari/Aii) times row i from row r in the matrix A.
 *
 *  Let's call (Ari/Aii) scalar. So, we want scalar times row i to be subtracted from row r for every r
 */
    auto n = M.size();
    auto r {i+1};
    double scalar;
    std::vector<double> srow_i;

    for (r = i+1; r < n; r++){

        //Calculate Ari, Aii, and scalar, initialise row r and srow_i
        auto Ari = M.at(r).at(i), Aii = M.at(i).at(i);
        scalar = Ari / Aii;
        auto& row_r = M.at(r);
        srow_i = M.at(i);

        //Calculate scalar * row_i = srow_i
        for(auto& el: srow_i){
            el *= scalar;//Multiplies every element of srow_i by scalar
        }

        //Subtract srow_i from row_r
        for(ull in = 0; in < row_r.size(); in++){
            row_r.at(in) -= srow_i.at(in);
        }
    }
}

void check_if_augsquare_matrix(const Matrix& A){//checks if a matrix is an augmented square matrix, throwing an int if it isn't
    //check if A is a nx(n+1) matrix
    //The vector A will be the n, the vectors within A will be the n+1
    //ie, n = A.size()
    for (const auto& i: A){
        //check if each element of A is of size n + 1, ie A.size()+1
//        std::cout << "i.size() = " << i.size() << std::endl;
//        std::cout << "A.size()+1 = " << A.size()+1 << std::endl;
        if (i.size() == A.size()+1);//Nothing happens if all is good
        else throw exception ("Error: Input is not an augmented square matrix.");
        //If Matrix A is too fat, just yeet an exception at main. Main is designed to catch
        //all exceptions, and print the exception message.
    }
}

void row_reduce(Matrix& M){
    /*  • For i = 0, 1, 2, . . . , n − 1
     *    – Find the index q ∈ {i, i + 1, . . . , n − 1} of the row with the largest value of |Aqi|.
     *    – Swap rows i and q in the matrix A.
     *    – If |Ai,i| < 0.0000001, no solution exists (see below).
     *    – For r = i + 1, i + 2, . . . , n − 1
     *          ∗ Subtract (Ari/Aii) times row i from row r in the matrix A.
    */
    ull q;
    for (ull i{0}; i < M.size(); i++){

        //Find the index q ∈ {i, i + 1, . . . , n − 1} of the row with the largest value of |Aqi|.
        q = find_largest_row_index(M, i);

        //Swap rows i and q in the matrix A.
        swap_rows(M, i, q);

        //If |Ai,i| < 0.0000001, no solution exists
        if (fabs(M.at(i).at(i)) <  0.0000001) throw exception ("Error: Matrix is ill-conditioned.");

        //For r = i + 1, i + 2, . . . , n − 1, subtract (Ari/Aii) times row i from row r in the matrix A.
        reduce_one_row(M, i);
    }
}

void back_substitute(const Matrix& M, std::vector<double>& x){
    auto n = M.size();//ie, n = the number of rows = n for the nxn matrix
    double t;//t will be set with an assignment statement later
    double M_in;//M_in is the element at row i, column n, of the augmented matrix. Will be assigned later.
    double cts;//crap to subtract
    x.clear();//Prepares the vector x to be used for only the subset of values produced by the pushback algorithm
    ull minus_1 = 0;
    minus_1--;

    //First, initialise x to be n elements long, each element having the value 0
    //The indices of x should be 0, 1, 2, ..., n-1
    //counter = 0, ..., n-1 eg if n=3 the indices of x are 0, 1, 2
    for(ull counter {0}; counter < n; counter++) x.push_back(0);
    for(ull i = n-1; i >= 0 && i != minus_1; i--){//for i = n-1, ..., 2, 1
        //im an idiot so I have to check if i ever reaches -1

        //initialise M_in, clear cts and t

        M_in = M.at(i).at(n);

        //cts and t should be set by the end of each iteration of the for loop
        cts = 0;
        t = 0;

        //calculate cts
        //For a 3x3 matrix...
        //This will be skipped in the first (ie, i = 2) iteration (since col = 3 = n)
        //In the second (and last) iteration (ie, i = 1), this only runs once, so it sets cts to the element at M_(1,2)
        for(auto col = i+1; col < n; col++){//col = i+1, ... , n-1
            cts += M.at(i).at(col) * x.at(col);

        }

        t = M_in - cts;//calculates t
        x.at(i) = t/M.at(i).at(i);//sets element i of x

    }
}

double det(const Matrix & A){//calculates the determinant of an upper-triangular matrix
	double product = 1;
	
	for (ull i; i < A.size(); i++) product *= A.at(i).at(i);
	
	return product;
}

/*
 * The plan:
 *
 * Step 1: Read the matrix from read_matrix function provided. If function fails, print error as specified, and
 * immediately go to the end of main (ie, exit with return code 0).
 *
 * Step 2: Check if the matrix is an augmented square matrix, and return an error as specified if it is not.
 *
 * Step 3: Row-reduce the matrix using the algorithm detailed in specifications
 *
 * Step 4: Back substitute
 */

int main(){
    Matrix A;
    try{
        //Step 1
        A = read_matrix();//A is a vector of vectors of doubles

        //Step 2
        check_if_augsquare_matrix(A);//returns an exception if A is not an augmented square matrix

        //Step 3
        row_reduce(A);//row reduces A, returning an exception if the matrix is ill conditioned
		
		if (det(A) < 0.0000001) throw exception ("Error: Matrix is ill-conditioned.");//Checks for singular matrices

        //Step 4
        std::vector<double> x;
        back_substitute(A,x);
        print(x);

    }catch(std::runtime_error& e){//Catches any errors read_matrix() throws
        std::cout << "Error: Unable to read input matrix." << std::endl;
    }catch(exception& e){//All the functions I have written throw an exception, of type string, which states what the error is.
        //Yha I wrote a bunch of this code before the lecture on exception types.
        std::cout << e << std::endl;
    }
    return 0;
}