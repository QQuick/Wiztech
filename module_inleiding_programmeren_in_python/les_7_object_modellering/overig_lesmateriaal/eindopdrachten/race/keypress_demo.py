import time as tm
import turtle as tr

class World:
    def __init__ (self):
        self.screen = tr.Screen ()
        self.screen.listen ()
        self.screen.onkey (self.printA, 'a')
        self.screen.onkey (self.printB, 'b')
        self.time = tm.time ()
        
    def printA (self):
        print ('AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA')
        
    def printB (self):
        print ('BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB')
        
    def run (self):
        while True:                 # Main real-time simulation loop
            # BEGIN mandatory statements
            self.oldTime = self.time
            self.time = tm.time ()  # The only place where the realtime clock is repeatedly queried
            self.deltaTime = self.time - self.oldTime
            # END mandatory statements
            
            # ... other code, using objects that are in the world, like a racetrack and cars
            
            print (self.deltaTime)
            self.screen.update ()
            tm.sleep (0.02)         # Needed to free up processor for other tasks like I/O

world = World ()
world.run ()
