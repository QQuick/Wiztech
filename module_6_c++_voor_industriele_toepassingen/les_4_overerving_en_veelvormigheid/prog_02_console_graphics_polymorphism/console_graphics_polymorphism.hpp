#pragma once

#include <list>
#include <vector>
#include <functional>

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
        Shape (Shape const &shape);
        void render (int maxFree);
        virtual void render () = 0;
        virtual float getDependent (int free) = 0;
};

class Circle: public Shape {
    friend class Canvas;
    
    public:
        Circle (Canvas &canvas, int radius, int xCenter = 0, int yCenter = 0);
        Circle (Circle const &circle);
        
    protected:
        int radius;

        void render ();
        virtual float getDependent (int free);
};

class Square: public Shape {
    friend class Canvas;
    
    public:
        Square (Canvas &canvas, int side, int x = 0, int y = 0);
        Square (Square const &square);
        
    private:
        int side;
        
        void render ();
        virtual float getDependent (int free);
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
        st::list <Circle> circles;              // Constructor will be called automagically
        st::list <Square> squares;              // "
        st::list <Shape *> shapes;              // "
        st::vector <st::vector <char> > rows;   // "
        int xCenter;
        int yCenter;
        
        void setCenter (int xCenter, int yCenter);
        void drawRelative (float x, float y);
};

}
