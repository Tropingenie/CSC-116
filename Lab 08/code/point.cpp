/* point.cpp
 * CSC 116 Fall 2019 - Lab 08
 */

#include <cmath>
#include <iostream>
#include "point.hpp"

// constructors

// student must implement this constructor
Point::Point(Point const & p) {
	mX = p.getX();
	mY = p.getY();
}

// student must implement this constructor
Point::Point(double x, double y) {
	mX = x;
	mY = y;
}

// student must implement this constructor
Point::Point() {
	mX = 0;
	mY = 0;
}

// return the X coordinate of the point
double Point::getX() const {
    // student code here
	return mX;
}

// return the Y coordinate of the point
double Point::getY() const {
    // student code here
	return mY;
}

// return a new point with the coordinates
// inverted:
//   the new point will have coordinates
// at (-getX(), -getY())
Point Point::operator-() const {
    // student code here
	Point r {-getX(),-getY()};
	return r;
}

// Add two points together
// should return a new point
Point Point::operator+(Point const & p2) const {
	// student code here
	Point r {getX()+p2.getX(), getY()+p2.getY()};
	return r;
}

// Multiple elements of the point by a scalar
// should return a new point
Point Point::operator*(double s) const {
	// student code here
	Point r {s*getX(), s*getY()};
	return r;
}

// compute the distance between the current
// point and the point p2
double Point::distance(Point const & p2) const {
    // student code here
	return sqrt ( pow(p2.getX() - getX(), 2) + pow(p2.getY() - getY(), 2) );//sqrt(deltaX^2 + deltaY^2)
}

// add the operator << to allow printing directly to a stream
std::ostream & operator<< (std::ostream & output, Point const & p) {
    // student code here
	std::cout << '[' << p.getX() << ',' << p.getY() << ']';
	return output;
}

std::ostream & operator<< (Point const & p, std::ostream & output) {
    // student code here
	return output << p;
}
