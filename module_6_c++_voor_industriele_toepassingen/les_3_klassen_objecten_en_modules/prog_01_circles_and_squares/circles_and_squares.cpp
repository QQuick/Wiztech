// Copyright: GEATEC engineering, 2020
// License: Apache 2

#include <iostream>
#include <vector>
#include <cmath>

namespace st = std;

class Canvas;

class Circle {
    friend class Canvas;
    
    public:
        Circle (Canvas &canvas, int radius, int xCenter = 0, int yCenter = 0);
        
    protected:
        Canvas &canvas;
        int radius;
        int xCenter;
        int yCenter;

        void render ();
};


class Square {
    friend class Canvas;
    
    public:
        Square (Canvas &canvas, int side, int x = 0, int y = 0);

    private:
        Canvas &canvas;
        int side;
        int xCenter;
        int yCenter;
        
        void render ();
};


class Canvas {
    friend class Circle;
    friend class Square;
    
    public:
        Canvas (int width = 64, int height = 48);
        void render ();
        
    protected:
        int width;
        int height;
        float xOrigin;
        float yOrigin;
        st::vector <Circle> circles;
        st::vector <Square> squares;
        st::vector <st::vector <char> > rows;
        int xCenter;
        int yCenter;
        
        void setCenter (int xCenter, int yCenter);
        void drawRelative (float x, float y);
};

// ====== Circle definitions
    
Circle::Circle (Canvas &canvas, int radius, int xCenter, int yCenter):
    canvas (canvas), radius (radius), xCenter (xCenter), yCenter (yCenter)
{
    canvas.circles.push_back (*this);
}

void Circle::render () {
    canvas.setCenter (xCenter, yCenter);
    
    for (auto free = -radius; free <= radius; free++) {
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
    canvas (canvas), side (side), xCenter (xCenter), yCenter (yCenter)
{
    canvas.squares.push_back (*this);
}

void Square::render () {
    canvas.setCenter (xCenter, yCenter);
    auto dependent = side / 2;
    
    for (auto free = -dependent; free <= dependent; free++) {
        
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

// ====== Main entrypoint

int main () {
    auto canvas = Canvas ();
        
    Circle (canvas, 16);
    Circle (canvas, 8, -14, -14);
    
    Square (canvas, 32);
    Square (canvas, 16, 14, 14);

    canvas.render ();
        
    return 0;
}
