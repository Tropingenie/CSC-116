#include "square.hpp"

Square::Square(Point const & min, double width): Rectangle { min.getX(), min.getY(), width, width} {
}
