#pragma once

#include <vector>
namespace st = std;

namespace consoleGraphics {

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
        Square (Canvas &canvas, int side, int x = 40, int y = 60);
        
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
        Canvas (int width = 0, int height = 0);
        void render ();
        
    protected:
        int width;
        int height;
        st::vector <Circle> circles;
        st::vector <Square> squares;
        st::vector <st::vector <char> > rows;
        int xCenter;
        int yCenter;
        
        void add (Circle circle);
        void add (Square square);
        void setCenter (int xCenter, int yCenter);
        void drawRelative (float x, float y);
};

}
