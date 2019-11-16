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