# (C) GEATEC engineering, license: Apache 2

import turtle as tr

triangle = ((0, 0), (50, 100), (100, 0))
box = ((0, 0), (0, 100), (100, 100), (100, 0))

boxedTriangle = tr.Shape ('compound')
boxedTriangle.addcomponent (box, 'blue')
boxedTriangle.addcomponent (triangle, 'red')

screen = tr.Screen ()
screen.setup (500, 500)
screen.register_shape ('boxed triangle', boxedTriangle)

pen = tr.Pen ()
pen.setheading (90)
pen.speed (1)
pen.shape ('boxed triangle')

pen.goto (-100, -50)
pen.down ()
pen.goto (100, 50)
pen.up ()

screen.update () 
