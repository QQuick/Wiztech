// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <iostream>
#include <cmath>
namespace st = std;

#include "console_graphics_polymorphism.hpp"

namespace consoleGraphics {
    
// ====== Canvas definitions
    
Shape::Shape (Canvas &canvas, int xCenter, int yCenter):
    canvas (canvas),
    xCenter (xCenter),
    yCenter (yCenter)
{
    // canvas.shapes.push_back (this);  // Will store temporary address, causing hidden bug
}

Shape::Shape (Shape const &shape):
    canvas (shape.canvas),
    xCenter (shape.xCenter),
    yCenter (shape.yCenter)
{
    canvas.shapes.push_back (this);     // Will store definitive address, acquired in copying to list
}

void Shape::render (int maxFree) {
    canvas.setCenter (xCenter, yCenter);
    
    for (auto free = -maxFree; free <= maxFree; free++) {
        auto dependent = getDependent (free);
        
        // Make x contiguous
        canvas.drawRelative (free, dependent);
        canvas.drawRelative (free, -dependent);
        
        // Make y contiguous
        canvas.drawRelative (dependent, free);
        canvas.drawRelative (-dependent, free);
    }
}

// ====== Circle definitions
    
Circle::Circle (Canvas &canvas, int radius, int xCenter, int yCenter):
    Shape (canvas, xCenter, yCenter),
    radius (radius)
{
    canvas.circles.push_back (*this);   // Will call copy constructor
}

Circle::Circle (Circle const &circle):
    Shape (circle),
    radius (circle.radius)   
{}

void Circle::render () {
    Shape::render (radius);
}

float Circle::getDependent (int free) {
    return sqrt (radius * radius - free * free);
}

// ====== Square definitions

Square::Square (Canvas &canvas, int side, int xCenter, int yCenter):
    Shape (canvas, xCenter, yCenter),
    side (side)
{
    canvas.squares.push_back (*this);   // Will call copy constructor
}

Square::Square (Square const &square):
    Shape (square),
    side (square.side)
{}

void Square::render () {
    Shape::render (side / 2);
}

float Square::getDependent (int free) {
    return side / 2;    
}

// ====== Canvas definitions

Canvas::Canvas (int width, int height):
    width (width),
    height (height),
    xOrigin (width / 2),
    yOrigin (height / 2)
{    
    for (auto rowIndex = 0; rowIndex < height; rowIndex++) {
        rows.emplace_back ();
        for (auto columnIndex = 0; columnIndex < width; columnIndex++) {
            rows [rowIndex] .push_back ('.');
        }
    }
}

void Canvas::render () {
    for (auto shape: shapes) {
        shape->render ();
        st::cout << shape << "  Shape\n";
    }
    
    for (auto &circle: circles) {
        st::cout << &circle << "  Circle\n";
    }
    
    for (auto &square: squares) {
        st::cout << &square << "  Square\n";
    }
    
    for (auto &row: rows) {
        for (auto &entry: row) {
           st::cout << " " << entry;
        }
        st::cout << '\n';
    }
}

void Canvas::setCenter (int xCenter, int yCenter) {
    this->xCenter = xCenter;
    this->yCenter = yCenter;
}

void Canvas::drawRelative (float x, float y) {
    rows [yCenter + yOrigin - y][xCenter + xOrigin + x - 1] = '*';
}

}
