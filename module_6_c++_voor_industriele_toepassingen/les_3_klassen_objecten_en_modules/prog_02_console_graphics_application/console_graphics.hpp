#pragma once

#include <vector>
#include <functional>

namespace st = std;

namespace consoleGraphics {

class Canvas;

class Circle {
    friend class Canvas;
    
    public:
        Circle (Canvas &canvas, int radius, int xCenter = 0, int yCenter = 0);
        Circle (Circle const &circle);
        
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
        Square (Square const &square);

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

}
