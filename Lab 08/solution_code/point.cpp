/* point.cpp
 * CSC 116 Fall 2019 - Lab 08
 */

#include <cmath>
#include "point.hpp"

// constructors

// Make a copy of a point
Point::Point(Point const & p) : mX{p.mX}, mY{p.mY} {
}

// create from two dimensions
Point::Point(double x, double y) : mX{x}, mY{y} {
}

// default constructor
Point::Point() : mX{0}, mY{0} {
}

// return the X coordinate of the point
double Point::getX() const {
    return mX;
}

// return the Y coordinate of the point
double Point::getY() const {
    return mY;
}

// return a new point with the coordinates
// inverted:
//   the new point will have coordinates
// at (-getX(), -getY())
Point Point::operator-() const {
    return Point(-mX, -mY);
}

// Add two points together
// should return a new point
Point Point::operator+(Point const & p2) const {
	return Point(mX + p2.mX, mY + p2.mY);
}

// Multiple elements of the point by a scalar
// should return a new point
Point Point::operator*(double s) const {
	return Point(mX * s, mY * s);
}

// compute the distance between the current
// point and the point p2
double Point::distance(Point const & p2) const {
    double dx = mX - p2.mX;
	double dy = mY - p2.mY;
	return std::sqrt(dx*dx + dy*dy);
}

// add the operator << to allow printing directly to a stream
std::ostream & operator<< (std::ostream & output, Point const & p) {
    output << "Point [" << p.getX() << ", " << p.getY() << "]";
    return output;
}

std::ostream & operator<< (Point const & p, std::ostream & output) {
    output << "Point [" << p.getX() << ", " << p.getY() << "]";
    return output;
}
