/* matrix.cpp

   CSC 116 Fall 2019 - Lab 7

*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
#include "matrix.hpp"
bool operator!= ( const std::pair<unsigned,unsigned>& p1,const std::pair<unsigned,unsigned>& p2){
  auto& [ox, oy] = p1; auto&[tx,ty] = p2;
  if (ox != tx || oy != ty) return true;
  else return false;
}

/* Constructor( num_rows, num_cols )
   Create a matrix of the given size, with all values
   set to zero.
*/
Matrix::Matrix(unsigned int num_rows, unsigned int num_cols) : Matrix (num_rows, num_cols, 0) {
    // Nothing to do here because we've called the other constructor above
}

/* Constructor( num_rows, num_cols, initial_value, default_value )
   Create a matrix of the given size, with all values
   set to the default value provided.
*/
Matrix::Matrix(unsigned int num_rows, unsigned int num_cols, double default_value) {
  std::vector<double> temp {};
  (*this).num_rows = num_rows; (*this).num_columns = num_cols;
  for (unsigned i{0}; i < num_rows; i++){
    for (unsigned i{0}; i < num_cols; i++){
      temp.push_back(default_value);
    }
    entries.push_back(temp);
  }
}

/* get_num_rows()
   Return the number of rows in the matrix
*/
unsigned int Matrix::get_num_rows() const {
  return num_rows;
}

/* get_num_cols()
   Return the number of columns in the matrix
*/
unsigned int Matrix::get_num_cols() const {
  return num_columns;
}

/* print()
   Output the matrix to standard output
*/
void Matrix::print() const {
  for (unsigned i {}; i < num_rows; i++){
    for (unsigned j {}; j < num_columns; j++){
      std::cout << entries.at(i).at(j) << " ";
    }
    std::cout << std::endl;
  }
}

/* at(i,j)
   Return a reference to the element at row i, column j.
   If the provided indices are out of range, throw an instance
   of std::out_of_range with the message "Invalid indices"
*/
double& Matrix::at(unsigned int i, unsigned int j) {
  try{
    auto& temp = entries.at(i).at(j);
    return temp;
  }catch(std::out_of_range& er){
    throw std::out_of_range("Invalid indices");
  }
}

std::pair<unsigned,unsigned> Matrix::size(){
  return std::make_pair(num_rows,num_columns);
}
std::pair<unsigned,unsigned> Matrix::size()const{
  return std::make_pair(num_rows,num_columns);
}

std::vector<double>& Matrix::at (unsigned i){
  auto& boop = entries.at(i);
  return boop;
}

/* at(i,j)
   Return a constant reference to the element at row i, column j.
   If the provided indices are out of range, throw an instance
   of std::out_of_range with the message "Invalid indices"
*/
double const & Matrix::at(unsigned int i, unsigned int j) const {
  try{
    const auto& temp = entries.at(i).at(j);
    return temp;
  }catch(std::out_of_range& er){
    throw std::out_of_range("Invalid indices");
  }
}
std::vector<double>& Matrix::at (unsigned i)const{
  const auto& boop = entries.at(i);
  return boop;
}

/* trace()
   Compute and return the trace of this matrix.

   The trace of a square matrix is the sum of the diagonal entries.
   For example, the trace of the matrix
      1 2 3
      4 5 6
      7 8 9
   is 15.

   If this matrix is not square, the method must throw a std::domain_error
   with message "Unable to compute trace of a non-square matrix".
*/
double Matrix::trace() const {
  if (num_rows != num_columns) throw std::domain_error("Unable to compute trace of a non-square matrix");
  auto trace = at(0,0);
  
  for(unsigned i {1}; i < num_columns; i++ ){
    trace += at(i,i);
  }
  
  return trace;
}


/* is_diagonal()
   Return true if this matrix is square and diagonal (that is, if all of the non-diagonal
   elements are 0) and false otherwise.
*/
bool Matrix::is_diagonal() const {
  if (num_rows != num_columns) return false;
  unsigned z {0};
  auto diag = std::make_pair(z,z);
  auto& [row,col] = diag;
  auto where = std::make_pair(z,z);
  auto& [curr_x,curr_y] = where;
  
  for(;curr_x < num_rows; curr_x++){
    for(;curr_y < num_columns; curr_y++){
      if( (where != diag) && (at(curr_x,curr_y) != 0) ) return false;
    }
    row++;
    col++;
  }
  return true;
}

/* *** Part 2 *** */

/* Methods of Matrix class */

/* operator- (other_matrix)
   Compute the difference between this matrix and the provided matrix
   and return the result.

   If the provided matrix does not have matching dimensions to this
   matrix, throw a std::domain_error with the message "Incompatible dimensions"
*/
Matrix Matrix::operator-( Matrix const & other_matrix ) const {
  if (entries.size() != other_matrix.size() || entries.at(0).size() != other_matrix.at(0).size() )
    throw std::domain_error ("Incompatible dimensions");//If matrices aren't of the same dimensions, throws an error
    
  Matrix diff {num_rows,num_columns};//makes a matrix the same size as *this
  
  for (unsigned i {0}; i < num_rows; i++){
    for (unsigned j {0}; j < num_columns; j++){
      diff.at(i,j) = at(i,j) - other_matrix.at(i,j);
    }
  }
  return diff;
}

/* operator+ (other_matrix)
   Compute the sum of this matrix and the provided matrix
   and return the result.

   If the provided matrix does not have matching dimensions to this
   matrix, throw a std::domain_error with the message "Incompatible dimensions"
*/
Matrix Matrix::operator+( Matrix const & other_matrix ) const {
  if (entries.size() != other_matrix.size() || entries.at(0).size() != other_matrix.at(0).size() )
    throw std::domain_error ("Incompatible dimensions");//If matrices aren't of the same dimensions, throws an error
    
  Matrix diff {num_rows,num_columns};//makes a matrix the same size as *this
  
  for (unsigned i {0}; i < num_rows; i++){
    for (unsigned j {0}; j < num_columns; j++){
      diff.at(i,j) = at(i,j) + other_matrix.at(i,j);
    }
  }
  return diff;
}

/* operator*(scalar)
   Compute and return the product of this matrix and the provided scalar value.
   This only covers multiplication by a scalar on the right. Multiplication
   by a scalar on the left cannot be handled by an operator which is part of the class.
*/
Matrix Matrix::operator*( double scalar ) const {
  Matrix diff {num_rows,num_columns};//makes a matrix the same size as *this
  
  for (unsigned i {0}; i < num_rows; i++){
    for (unsigned j {0}; j < num_columns; j++){
      diff.at(i,j) = at(i,j) * scalar;
    }
  }
  return diff;
}


/* Functions outside Matrix class */


/* operator*( scalar, M )
   Compute and return the product of the provided scalar and provided matrix.
   Note that this operator is not part of the Matrix class, and therefore
   does not have access to the private members of that class, unless you add
   a friend directive for it.
*/
// NOTE: this function must be implemented outside the class because its first arg is not a Matrix object
Matrix operator*( double scalar, Matrix const &  M ) {
  Matrix diff = M * scalar;
  return diff;
}

/* Floating point types should never be compared for equality directly,
   since they have inherent inaccuracies. Instead, use the function below
   to test whether two doubles are equal to within a tolerance of 10^{-7}.
*/
bool doubles_equal( double a, double b ) {
 auto tmp = fabs( a - b );
 
 if (tmp <= 10^(-7) ) return true;
 else return false;
}

/* operator==( M1, M2 )
   Return true if M1 and M2 have the same dimensions and
   are equal (element-wise) and false otherwise.

   Use the doubles_equal function above to compare values.
*/
bool operator==(Matrix const & M1, Matrix const & M2) {
  if (entries.size() != other_matrix.size()) return false;
  for (unsigned i {0}; i < M1.size().first; i++){
    for (unsigned j {0}; j < M2.size().second; j++){
      if (!doubles_equal( M1.at(i,j) , M2.at(i,j) ) ) return false;
    }
  }
  return true;//else
}

/* operator!=( M1, M2 )
   Return true if M1 and M2 are not equal. This should
   have the opposite behavior to the == operator.
*/
bool operator!=(Matrix const & M1, Matrix const & M2) {
  if ( M1 == M2 ) return false;
  else return true;
}
