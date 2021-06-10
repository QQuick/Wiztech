import turtle as tr
import time as tm
import math as mt
import random as rd

# Everything in SI units and radians, unless stated otherwise

def getDistance (x0, y0, x1, y1):
    return mt.sqrt ((x1 - x0) ** 2 + (y1 - y0) ** 2)

def getRectangle (world, width, height, xShift = 0, yShift = 0):
    width *= world.resolution
    height *= world.resolution
    xShift *= world.resolution
    yShift *= world.resolution
    
    return (
        (-width / 2 + xShift, -height / 2 + yShift),
        (-width / 2 + xShift, height / 2 + yShift),
        (width / 2 + xShift, height / 2 + yShift),
        (width / 2 + xShift, -height / 2 + yShift)
    )
    
class Thing:
    def __init__ (self, world, x, y):
        self.world = world
    
        if self.world:
            self.x, self.y = x, y
            
            self.pen = tr.Pen ()
            self.pen.speed (0)
            self.pen.up ()
            
            self.goto (self.x, self.y)
                        
    def compute (self):
        pass
        
    def render (self):
        pass
        
    def setheading (self, angle):
        self.pen.setheading (angle * 180 / mt.pi)
        
    def goto (self, x, y):
        self.pen.goto (x * self.world.resolution, y * self.world.resolution)
        
    def penUndoableDummy (self):
        self.goto (self.x, self.y)

class Timer (Thing):
    def __init__ (self, world = None, x = None, y = None):
        super () .__init__ (world, x, y)
        self.time = tm.time ()
                
        if self.world:
            self.pen.color ('cyan')
            self.pen.hideturtle ()
            self.penUndoableDummy ()
        
    def compute (self):
        self.oldTime = self.time
        self.time = tm.time ()
        self.deltaTime = self.time - self.oldTime
        
    def render (self):
        if self.world:
            if int (self.time) > int (self.oldTime):
                self.pen.undo ()
                self.pen.write (
                    tm.strftime ('%H:%M:%S', tm.localtime (self.time)),
                    font = ('Arial', 40, 'normal')
                )

class Car (Thing):
    def __init__ (self, world, x, y, color):
        super () .__init__ (world, x, y)

        self.width, self.length = 1.6, 4.5
        cabinColor = 'indigo'
        shape = tr.Shape ('compound')
        shape.addcomponent (getRectangle (self.world, self.width, self.length), color, color)
        
        shape.addcomponent (getRectangle (self.world, 1.2, 2, yShift = -0.5), cabinColor, cabinColor)
        self.world.screen.register_shape (color, shape)
        self.pen.shape (color)
        
        self.speed = 0
        self.vertexIndex, self.edgeLengthTraveled = 0, 0
        self.x, self.y = 1e4, 1e4
        self.angle, self.angleSample = 0, 0
        self.slipping, self.slipSampleTimer, self.slipSampleTime = False, 0, 0.3 
        
    def setKeys (self, brakeKey, acceleratorKey):
        self.world.screen.onkey (self.accelerate, acceleratorKey)
        self.world.screen.onkey (self.brake, brakeKey)
        
    def compute (self):
        self.distanceToTravel = self.speed * self.world.timer.deltaTime
        
        if self.slipping:
            self.x += self.distanceToTravel * mt.cos (self.slipAngle)
            self.y += self.distanceToTravel * mt.sin (self.slipAngle)
            self.angle += rd.random () - 0.5
        else:
            self.world.track.advance (self)
            
            self.slipSampleTimer += self.world.timer.deltaTime
            if self.slipSampleTimer > self.slipSampleTime:
                absDeltaAngle = abs (self.angleSample - self.angle)
                
                if 0 < absDeltaAngle < mt.pi:
                    angularVelocity = absDeltaAngle / self.slipSampleTime
                    curveRadius =  getDistance (self.x, self.y, self.xSample, self.ySample) / mt.sin (absDeltaAngle)
                    if angularVelocity ** 2 * curveRadius > 100:
                        self.slipAngle = self.angle
                        self.slipping = True

                self.slipSampleTimer = 0
                self.angleSample = self.angle
                self.xSample = self.x
                self.ySample = self.y         
        
    def render (self):
        self.setheading (self.angle)
        self.goto (self.x, self.y)
        
    def accelerate (self):
        self.speed = min (self.speed + 5, 100)
        
    def brake (self):
        self.speed = max (self.speed - 7, 0)
        
class Track (Thing):
    def __init__ (self, world):
        super () .__init__ (world, 0, 0)
        self.polygon = []
        self.building = True

        self.world.screen.onkey (self.stopBuilding, '\n')
        self.world.screen.onclick (self.handleClick)
        
        self.width = 5
        self.centerShiftFraction = 0.6   # Fraction of carwidth between car center and track center
        
        self.pen.width (self.world.resolution * self.width)
        self.pen.color ('black')

    def stopBuilding (self):
        if self.building:
            self.goto (*self.polygon [0])
            self.building = False
            for car in self.world.cars:
                car.x, car.y = self.polygon [0]
                car.xSample, car.ySample = car.x, car.y
                car.distanceToTravel = 1e-3
                self.advance (car)
                car.angleSample = car.angle
                
    def handleClick (self, x, y):
        if self.building:
            print ('Added track point')
            self.polygon.append ((x / self.world.resolution, y / self.world.resolution))        
            self.goto (*self.polygon [-1])
            self.pen.down ()
    
    def advance (self, car):
        if len (self.polygon) and not self.building and car.distanceToTravel > 0:
            while car.distanceToTravel > 0:
                vertex = self.polygon [car.vertexIndex]
                nextVertex = self.polygon [(car.vertexIndex + 1) % len (self.polygon)]
                
                deltaX = nextVertex [0] - vertex [0]
                deltaY = nextVertex [1] - vertex [1]
                
                edgeLength = mt.sqrt (deltaX ** 2 + deltaY ** 2)
                
                edgeLengthToTravel = edgeLength - car.edgeLengthTraveled
                if edgeLengthToTravel > car.distanceToTravel:
                    car.edgeLengthTraveled += car.distanceToTravel
                    car.distanceToTravel = 0
                else:
                    car.edgeLengthTraveled = car.distanceToTravel - edgeLengthToTravel
                    car.vertexIndex = (car.vertexIndex + 1) % len (self.polygon)
                    car.distanceToTravel -= edgeLengthToTravel

            isRightCar = car == self.world.rightCar
            normalUnitX = (deltaY if isRightCar else -deltaY) / edgeLength
            normalUnitY = (-deltaX if isRightCar else deltaX) / edgeLength
            
            car.x = vertex [0] + deltaX * car.edgeLengthTraveled / edgeLength + normalUnitX * self.centerShiftFraction * car.width
            car.y = vertex [1] + deltaY * car.edgeLengthTraveled / edgeLength + normalUnitY * self.centerShiftFraction * car.width
            car.angle = mt.atan2 (deltaY, deltaX)
            
    def compute (self):
        cars = self.world.cars
        if (
            4 < abs (cars [0] .vertexIndex - cars [1] .vertexIndex) < len (self.polygon) - 4 and
            getDistance (cars [0] .x, cars [0] .y, cars [1] .x, cars [1] .y) < self.world.collisionDistance
        ):
            print (cars [0] .vertexIndex, cars [1] .vertexIndex)
            for car in cars:
                car.slipAngle = car.angle
                car.slipping = True
    
class World:
    def __init__ (self): 
        self.resolution = 20     # Pixels / meter
    
        self.screen = tr.Screen ()
        self.screen.setup (
            width = 1.0,        # Width of physical screen, ca 1920 pixels, 96 meter
            height = 1.0        # Height of physical screen, ca 1080 pixels, 54 meter
        )
        self.screen.delay (0)
        self.screen.listen ()
        self.screen.bgpic ('background.gif')
        
        self.timer = Timer (self, -45, 20)
        self.track = Track (self)
        
        self.leftCar = Car (self, 0, 0, 'red')
        self.rightCar = Car (self, 20, -20, 'blue')
        
        self.collisionDistance = 0.4 * (self.leftCar.length + self.rightCar.length)
        
        self.leftCar.setKeys ('z', 'a')
        self.rightCar.setKeys ('m', 'k')  
        
        self.cars = (self.leftCar, self.rightCar)
        self.things = (self.timer, self.track) + self.cars
        
        self.run ()
        
    def run (self):
        while True:
            for thing in self.things:
                thing.compute ()
                
            for thing in self.things:
                thing.render ()
                
            self.screen.update ()
            tm.sleep (0.02)
            
        
World ()
