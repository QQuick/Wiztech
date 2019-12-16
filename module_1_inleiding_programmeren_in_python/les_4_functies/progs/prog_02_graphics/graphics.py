import turtle as tr

aspectRatio = tr.window_height () / tr.window_width ()

xMax = 1000
xMin = -xMax
yMax = xMax * aspectRatio
yMin = -yMax

tr.setworldcoordinates (xMin, yMin, xMax, yMax)

turtle = tr.Turtle ()
turtle.penup ()
input ('Gebruik de [enter] toets om te beginnen met tekenen')

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
    turtle.goto (xCenter, yCenter - radius)
    turtle.pendown ()
    turtle.circle (radius)
    turtle.penup ()

bottom = -500

towerLeft = -600
towerRight = -200
towerAttic = 300
peakTop = 800
towerMiddle = (towerLeft + towerRight) // 2

aisleRight = 600
aisleAttic = -100

roofRight = 400
roofTop = 100

towerWindowWidth = 40
aisleWindowWidth = 70

drawRectangle (towerLeft, bottom, towerRight, towerAttic, True)
drawTriangle (towerLeft, towerAttic, towerMiddle, peakTop, towerRight, towerAttic, True)

drawRectangle (towerRight, bottom, aisleRight, aisleAttic, True)
drawLine (aisleRight, aisleAttic, roofRight, roofTop, True)
drawLine (roofRight, roofTop, towerRight, roofTop, True)

for towerWindowIndex in range (3):
    windowBottom = bottom + 100 + towerWindowIndex * 200
    drawRectangle (towerMiddle - towerWindowWidth // 2, windowBottom, towerMiddle + towerWindowWidth // 2, windowBottom + 150)

for aisleWindowIndex in range (3):
    windowLeft = towerRight + 150 + aisleWindowIndex * 200
    drawRectangle (windowLeft, bottom + 100, windowLeft + aisleWindowWidth, bottom + 300)
    
drawCircle (towerMiddle, towerAttic + 150, 50)
    
horizon = bottom + 200
    
drawLine (xMin, horizon, towerLeft, horizon)
drawLine (aisleRight, horizon, xMax, horizon)

while True:
    pass

