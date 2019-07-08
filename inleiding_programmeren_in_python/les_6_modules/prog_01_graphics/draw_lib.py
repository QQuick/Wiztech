import turtle as tr

aspectRatio = tr.window_height () / tr.window_width ()

xMax = 1000
xMin = -xMax
yMax = xMax * aspectRatio
yMin = -yMax

tr.setworldcoordinates (xMin, yMin, xMax, yMax)

turtle = tr.Turtle ()
turtle.penup ()

def drawLine (x0, y0, x1, y1, thick = False):
    turtle.width (5 if thick else 1)
    turtle.goto (x0, y0)
    turtle.pendown ()
    turtle.goto (x1, y1)
    turtle.penup ()

def drawTriangle (x0, y0, x1, y1, x2, y2, thick = False):
    drawLine (x0, y0, x1, y1, thick)
    drawLine (x1, y1, x2, y2, thick)
    drawLine (x2, y2, x1, y1, thick)

def drawRectangle (x0, y0, x1, y1, thick = False):
    drawLine (x0, y0, x0, y1, thick)
    drawLine (x0, y1, x1, y1, thick)
    drawLine (x1, y1, x1, y0, thick)
    drawLine (x1, y0, x0, y0, thick)
    
def drawCircle (xCenter, yCenter, radius, thick = False):
    turtle.width (5 if thick else 1)
    turtle.goto (xCenter, yCenter -radius)
    turtle.pendown ()
    turtle.circle (radius)
    turtle.penup ()
