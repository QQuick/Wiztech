#include "console_graphics.hpp"

namespace cg = consoleGraphics;

int main () {
    auto canvas = cg::Canvas ();
    
    auto largeCircle = cg::Circle (canvas, 10, 7, 9);
    auto smallCircle = cg::Circle (canvas, 5);
    
    auto largeSquare = cg::Square (canvas, 16, 14, 16);
    auto smallSquare = cg::Square (canvas, 8);
    
    canvas.render ();
    return 0;
}
