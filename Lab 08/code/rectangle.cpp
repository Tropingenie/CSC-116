/*
 * rectangle.cpp
 * CSC 116 Fall 2019 - Lab 08
 */

#include "rectangle.hpp"

// student must implement this constructor
Rectangle::Rectangle(Point const & min, Point const & max): mMin{min}, mMax{max} {
	w = (mMax.getX() - mMin.getX());
	h = (mMax.getY()-mMin.getY());
	a = w*h;
}

// student must implement this constructor
Rectangle::Rectangle(double x, double y, double width, double height): mMin{x,y}, mMax{x + width, y + height} {
	w = width;
	h = height;
	a = width * height;
}

double Rectangle::area() const {
    // student code here
	return a;
}

double Rectangle::perimeter() const {
    // student code here
	return (2*w) + (2*h);
}

Point Rectangle::center() const {
    // student code here
	double x = mMax.getX() + mMin.getX();
	double y = mMax.getY() + mMin.getY();
	Point centre {x/2.0,y/2.0};
	return centre;
}

std::string Rectangle::name() const {
    // student code here
	return "Rectangle";
}

double Rectangle::width() const {
    // student code here
	return w;
}

double Rectangle::height() const {
    // student code here
	return h;
}

Point Rectangle::getMin() const {
	// student code here
	return mMin;
}

Point Rectangle::getMax() const {
	// student code here
	return mMax;
}
