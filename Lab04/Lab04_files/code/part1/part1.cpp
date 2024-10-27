/* part1.cpp
   CSC 116 - Fall 2019 - Lab 4
   
*/
#include <iostream>
#include <vector>

// Define a type Matrix which is a vector of vectors containing doubles.
using matrix_type = std::vector< std::vector< double > >;

/* Functions to complete */


/* add_matrices(A, B)
   Compute the (pointwise) sum of matrices A and B and return it.
   
   For part 1, you may assume that A and B have compatible dimensions.
   
   QUESTION: The parameters to ~add_matrices~ (in both parts) have type ~const matrix_type&~. 
   		Why would this type be a better choice than the plain ~matrix_type~ type?
*/
matrix_type add_matrices( const matrix_type& A, const matrix_type& B ){
	matrix_type matrix_sum = A;
	unsigned int i = 0;
	unsigned int j = 0;

	for(i=0; i < A.size(); i++){
		for (j=0; j < A.at(0).size(); j++){
			matrix_sum.at(i).at(j) += B.at(i).at(j);
		}
	}

	return matrix_sum;
}

/* identity(n)
   Compute and return the n x n identity matrix.
   
   Recall that the identity matrix of size n has 1s on the diagonal and
   0s everywhere else.
   
*/

matrix_type identity( unsigned int n ){
	matrix_type I;
	std::vector<double> row;
	unsigned int position = 0;

	for (unsigned int count = 0; count < n; count++){
		for (unsigned int count = 0; count < n; count++){
			if (position == count) row.push_back(1);
			else row.push_back(0);
		}
		I.push_back(row);
		row.clear();
		position++;
	}


	return I;
}

/* hilbert(n)
   Compute and return the n x n Hilbert matrix.
   
   The Hilbert matrix has entry (i,j) set to 1/(i + j - 1), for
   each row i and column j in the range (1,2,3,..., n).
   Note: that in the definition above, row indices and column
   indices start at 1, not 0.
   
   For example, the 3x3 Hilbert matrix is
	1    1/2  1/3
	1/2  1/3  1/4 
	1/3  1/4  1/5
   
*/

matrix_type hilbert( unsigned int n ){
	matrix_type H;
	std::vector<double> row;
	double number;

	for (unsigned int i = 0; i < n; i++){
		for (unsigned int j = 0; j < n; j++){
			double floati = i; 
			double floatj = j;
			number = 1/(floati+floatj+1);
			row.push_back(number);
		}
		H.push_back(row);
		row.clear();
	}
	return H;
}



/* End of functions to complete */

/* QUESTION: The ~print_matrix~ function in both parts uses "for-each" style loops instead of traditional index-based loops. 
		Can the ~add_matrices~ function be written with for-each loops? Why or why not?
*/
void print_matrix( matrix_type M ){
	for (auto row: M){
		for(auto entry: row) {
			std::cout << entry << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
   
	int n {};
	
	std::cout << "Enter the value of n: ";
	if (!(std::cin >> n) || (n <= 0) ){
		std::cout << "Invalid value for n." << std::endl;
		return 1;
	}
	
	matrix_type I { identity(n) };
	std::cout << "Identity (" << n << " x " << n << "):" << std::endl;
	print_matrix(I);
	
	matrix_type H { hilbert(n) };
	std::cout << "Hilbert (" << n << " x " << n << "):" << std::endl;
	print_matrix(H);
	
	
	matrix_type S { add_matrices(I,H) };
	std::cout << "Sum of I and H:" << std::endl;
	print_matrix(S);
	
    return 0;
}
