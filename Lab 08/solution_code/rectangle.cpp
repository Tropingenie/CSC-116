/*
 * rectangle.cpp
 * CSC 116 Fall 2019 - Lab 08
 */

#include "rectangle.hpp"

Rectangle::Rectangle(Point const & min, Point const & max) : mMin{min}, mMax{max} {
}

Rectangle::Rectangle(double x, double y, double width, double height): mMin {x,y}, mMax{x+width,y+height} {
}

double Rectangle::area() const {
    return width()*height();
}

double Rectangle::perimeter() const {
    return 2*(width() + height());
}

Point Rectangle::center() const {
    return (mMin + mMax) * 0.5;
}

std::string Rectangle::name() const {
    return "Rectangle";
}

double Rectangle::width() const {
    return mMax.getX() - mMin.getX();
}

double Rectangle::height() const {
    return mMax.getY() - mMin.getY();
}

Point Rectangle::getMin() const {
	return mMin;
}

Point Rectangle::getMax() const {
	return mMax;
}
