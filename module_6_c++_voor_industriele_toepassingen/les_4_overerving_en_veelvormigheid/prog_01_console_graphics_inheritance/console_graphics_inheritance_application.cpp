#include "console_graphics_inheritance.hpp"

namespace cg = consoleGraphics;

int main () {
    auto canvas = cg::Canvas ();
        
    cg::Circle (canvas, 16);
    cg::Circle (canvas, 8, -14, -14);
    
    cg::Square (canvas, 32);
    cg::Square (canvas, 16, 14, 14);

    canvas.render ();
        
    return 0;
}
