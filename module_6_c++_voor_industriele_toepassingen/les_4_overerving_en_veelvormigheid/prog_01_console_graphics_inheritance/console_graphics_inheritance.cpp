#include <iostream>
#include <cmath>

#include "console_graphics_inheritance.hpp"

namespace consoleGraphics {
    
// ====== Canvas definitions
    
Shape::Shape (Canvas &canvas, int xCenter, int yCenter):
    canvas (canvas),
    xCenter (xCenter),
    yCenter (yCenter)
{}

void Shape::render () {
    canvas.setCenter (xCenter, yCenter);
}

// ====== Circle definitions
    
Circle::Circle (Canvas &canvas, int radius, int xCenter, int yCenter):
    Shape (canvas, xCenter, yCenter),
    radius (radius)
{
    canvas.circles.push_back (*this);
}

Circle::Circle (Circle const &circle):
    Shape (circle.canvas, circle.xCenter, circle.yCenter),
    radius (circle.radius)   
{}

void Circle::render () {
    Shape::render ();
    
    for (int free = -radius; free <= radius; free++) {
        auto dependent = sqrt (radius * radius - free * free);
        
        // Make x contiguous
        canvas.drawRelative (free, dependent);
        canvas.drawRelative (free, -dependent);
        
        // Make y contiguous
        canvas.drawRelative (dependent, free);
        canvas.drawRelative (-dependent, free);
    }
}

// ====== Square definitions

Square::Square (Canvas &canvas, int side, int xCenter, int yCenter):
    Shape (canvas, xCenter, yCenter),
    side (side)
{
    canvas.squares.push_back (*this);
}

Square::Square (Square const &square):
    Shape (square.canvas, square.xCenter, square.yCenter),
    side (square.side)
{}

void Square::render () {
    Shape::render ();
    auto dependent = side / 2;
    
    for (int free = -dependent; free <= dependent; free++) {
        
        // Make x contiguous
        canvas.drawRelative (free, dependent);
        canvas.drawRelative (free, -dependent);
        
        // Make y contiguous
        canvas.drawRelative (dependent, free);
        canvas.drawRelative (-dependent, free);
    }        
}

// ====== Canvas definitions

Canvas::Canvas (int width, int height):
    width (width),
    height (height),
    xOrigin (width / 2),
    yOrigin (height / 2)
{
    circles = st::vector <Circle> ();
    squares = st::vector <Square> ();
    
    for (auto rowIndex = 0; rowIndex < height; rowIndex++) {
        rows.emplace_back ();
        for (auto columnIndex = 0; columnIndex < width; columnIndex++) {
            rows [rowIndex] .push_back ('.');
        }
    }
}

void Canvas::render () {
    for (auto &circle: circles) {
        circle.render ();;
    }
    
    for (auto &square: squares) {
        square.render ();
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
