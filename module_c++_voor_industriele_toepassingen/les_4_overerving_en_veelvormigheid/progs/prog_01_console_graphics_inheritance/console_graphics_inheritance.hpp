// Copyright: GEATEC engineering, 2020
// License: Apache 2

#pragma once

#include <vector>
namespace st = std;

namespace consoleGraphics {

class Canvas;

class Shape {
    friend class Canvas;
            
    protected:
        Canvas &canvas;
        int xCenter;
        int yCenter;

        Shape (Canvas &canvas, int xCenter = 0, int yCenter = 0);
        void render ();
};

class Circle: Shape {
    friend class Canvas;
    
    public:
        Circle (Canvas &canvas, int radius, int xCenter = 0, int yCenter = 0);
        
    protected:
        int radius;

        void render ();
};

class Square: Shape {
    friend class Canvas;
    
    public:
        Square (Canvas &canvas, int side, int x = 0, int y = 0);
        
    protected:
        int side;
        
        void render ();
};


class Canvas {
    friend class Shape;
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
