class Canvas {
    friend class Circle;
    friend class Square;
    
public:
    Canvas (int width = 0, height = 0):
        width (width),
        height (height)
    {
        circles = st::vector <Circle>
        squares = st::vector <Square>
        
        for (rowIndex = 0; rowIndex < height; rowIndex++) {
            rows.emplace_back ();
            for (columnIndex = 0; columnIndex < width; columnIndex++) {
                rows [rowIndex] .push_back ('.');
            }
        }
    }

protected:
    void add (Circle circle) {
        circles.push_back (circle);
        
    void add (Square square);
        squares.push_back (square);
        
    void render () {
        for (auto circle: circles) {
            circle.render ();
        }
        
        for (auto square: squares) {
            square.render ();
        }
    }
    
    void setCenter (int xCenter, int yCenter) {
        this->xCenter = xCenter;
        this->yCenter = yCenter;
    }
    
    void drawRelative (x, y) {
        buffer [int (xCenter + x)][int (yCenter + y)];
    }
};

class Circle {
    friend class Canvas;
public:
    Circle (Canvas &canvas, int radius, int xCenter = 0, int yCenter = 0):
        canvas (canvas), radius (radius), xCenter (xCenter), yCenter (yCenter)
    {}
    
protected:
    auto &canvas = Canvas ();
    auto radius = 0;
    auto xCenter = 0;
    auto yCenter = 0;
    
    void render () {
        canvas.setCenter (xCenter, yCenter);
        
        for (int i = -radius); i <= radius; i++) {
            j = sqrt (radius * radius - i * i);
                        
            // Make x contiguous
            canvas.drawRelative (i, j);
            canvas.drawRelative (i, -j);
            
            // Make y contiguous
            canvas.drawRelative (j, i);
            canvas.drawRelative (j, -i);
        }
    }
};

class Square {
    friend class Canvas;
public:
    Square (Canvas &canvas, int side, int x = 0, int y = 0):
        canvas (canvas), side (side), x (x), y (y))
    {}
    
private:
    auto &canvas = Canvas ();
    auto side = 0;
    auto xCenter = 0;
    auto yCenter = 0;
    
    void render () {
        canvas.setCenter (xCenter, yCenter);

        for (int i = -radius; i <= radius; i++) {
            // Make x contiguous
            canvas.drawRelative (i, radius);
            canvas.drawRelative (i, -radius);
            
            // Make y contiguous
            canvas.drawRelative (radius, i);
            canvas.drawRelative (-radius, i);
        }        
    }
};

int main () {
    auto canvas = Canvas ();
    
    auto largeCircle = Circle (canvas, 10, 7, 9);
    auto smallCircle = Circle (canvas, 5);
    
    auto largeSquare = Square (canvas, 16, 14, 16);
    auto smallSquare = Square (canvas, 8);
    
    return 0;
}
