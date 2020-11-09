import math as mt
import random as rd
import curses as cs
import curses.ascii as ca
import time as tm
 
orthoWidth = 1500
orthoHeight = 750
fieldHeight = 650

a, z, k, m = 'a', 'z', 'k', 'm'
enter, escape, space, resize = cs.KEY_ENTER, ca.ESC, ' ', cs.KEY_RESIZE
pixelChar = '*'

class Attribute:    # Attribute in the gaming sense of the word, rather than of an object
    def __init__ (self, game):
        self.game = game                    # Attribute knows game it's part of
        self.game.attributes.append (self)  # Game knows all its attributes
        self.reset ()                       # Reset attribute to start position
        
    def install (self):
        pass
                    
    def reset (self):       # Restore starting positions or score, then commit to curses
        self.commit ()      # Nothing to restore for the Attribute base class
                
    def predict (self):
        pass
                
    def interact (self):
        pass
        
    def commit (self):
        pass
       
class Sprite (Attribute):   # Here, a sprite is an attribute that can move
    def __init__ (self, game, width, height):
        self.width = width
        self.height = height
        Attribute.__init__ (self, game)
        
    def install (self):     # The sprite holds a cursesSprite, that curses can display
        self.cursesSprite = (self.width, self.height)
        
    def reset (self, vX = 0, vY = 0, x = orthoWidth // 2, y = fieldHeight // 2):
        self.vX = vX        # Speed
        self.vY = vY
        
        self.x = x          # Predicted position, can be commit, no bouncing initially
        self.y = y
        
        Attribute.reset (self)
        
    def predict (self):     # Predict position, do not yet commit, bouncing may alter it
        self.x += self.vX * self.game.deltaT
        self.y += self.vY * self.game.deltaT

    def commit (self):      # Draw cursesSprite)
        for x in range (int (self.x) - self.width // 2, int (self.x) + self.width // 2, self.game.charWidthInOrtho):
            for y in range (int (self.y) - self.height // 2, int (self.y) + self.height // 2, self.game.charHeightInOrtho):
                self.game.draw (x, y, '*')
         
class Paddle (Sprite):
    margin = 30 # Distance of paddles from walls
    width = 10
    height = 100
    speed = 800 # / s
    
    def __init__ (self, game, index):
        self.index = index  # Paddle knows its player index, 0 == left, 1 == right
        Sprite.__init__ (self, game, self.width, self.height)
        
    def reset (self):       # Put paddle in rest position, dependent on player index
        Sprite.reset (
            self,
            x = orthoWidth - self.margin if self.index else self.margin,
            y = fieldHeight // 2
        )
        
    def predict (self): # Let paddle react on keys
        self.vY = 0
        
        if self.index:  # Right player
            if self.game.key == k:
                self.vY = self.speed
            elif self.game.key == m:
                self.vY = -self.speed
        else:           # Left player
            if self.game.key == a:
                self.vY = self.speed
            elif self.game.key == z:
                self.vY = -self.speed
                
        Sprite.predict (self)   # Do not yet commit, paddle may bounce with walls

    def interact (self):        # Paddles and ball assumed infinitely thin
        # Paddle touches wall
        self.y = max (self.height / 2, min (self.y, fieldHeight - self.height / 2))
        
        # Paddle hits ball
        if (
            (self.y - self.height // 2) < self.game.ball.y < (self.y + self.height // 2)
            and (
                (self.index == 0 and self.game.ball.x < self.x) # On or behind left paddle
                or
                (self.index == 1 and self.game.ball.x > self.x) # On or behind right paddle
            )
        ):
            self.game.ball.x = self.x               # Ball may have gone too far already
            self.game.ball.vX = -self.game.ball.vX  # Bounce on paddle
        
            speedUp = 1 + 0.5 * (1 - abs (self.game.ball.y - self.y) / (self.height // 2)) ** 2
            self.game.ball.vX *= speedUp            # Speed will increase more if paddle near centre
            self.game.ball.vY *= speedUp
                    
class Ball (Sprite):
    side = 8
    speed = 300 # / s
    
    def __init__ (self, game):
        Sprite.__init__ (self, game, self.side, self.side)
 
    def reset (self):   # Launch according to service direction with rd angle offset from horizontal
        angle =  (
            self.game.serviceIndex * mt.pi    # Service direction
            +
            rd.choice ((-1, 1)) * rd.random () * mt.atan (fieldHeight / orthoWidth)
        )
        
        Sprite.reset (
            self,
            vX = self.speed * mt.cos (angle),
            vY = self.speed * mt.sin (angle)
        )
        
    def predict (self):
        Sprite.predict (self)       # Integrate velocity to position

        if self.x < 0:              # If out on left side
            self.game.scored (1)    #   Right player scored
        elif self.x > orthoWidth:
            self.game.scored (0)
            
        if self.y > fieldHeight:    # If it hit top wall
            self.y = fieldHeight    #   It may have gone too far already
            self.vY = -self.vY      #   Bounce
        elif self.y < 0:
            self.y = 0
            self.vY = -self.vY

class Scoreboard (Attribute):
    nameShift = 75
    scoreShift = 45
        
    def increment (self, playerIndex):
        self.scores [playerIndex] += 1
    
    def reset (self):
        self.scores = [0, 0]
        Attribute.reset (self)                  # Only does a commit here
        
    def commit (self):                          # With curses, the whole scoreboard is simply drawn each time 
        self.game.draw (1 * orthoWidth // 4, fieldHeight + self.nameShift, 'Speler AZ')                     # Player name
        self.game.draw (3 * orthoWidth // 4, fieldHeight + self.nameShift, 'Speler KM')
 
        self.game.draw (1 * orthoWidth // 4, fieldHeight + self.scoreShift, '{}'.format (self.scores [0]))  # Player score
        self.game.draw (3 * orthoWidth // 4, fieldHeight + self.scoreShift, '{}'.format (self.scores [1]))
 
        for x in range (0, orthoWidth, self.game.charWidthInOrtho):                                         # Line
            self.game.draw (x, fieldHeight, pixelChar)
    
class Game:
    def __init__ (self):
        self.serviceIndex = rd.choice ((0, 1))  # Index of player that has initial service
        self.pause = True                       # Start game in paused state
        self.key = ''
        
        self.attributes = []                    # All attributes will insert themselves here
                
        def run (screen):                       # Install update callback to be called 50 times per s
            self.screen = screen
            self.screen.nodelay (True)
            cs.curs_set (False)
            
            self.resize ()                      # Elementary timestep of simulation
            self.paddles = [Paddle (self, index) for index in range (2)]    # Pass game as parameter self
            self.ball = Ball (self)
            self.scoreboard = Scoreboard (self)
            
            time = tm.time ()
            
            while True:
                oldTime = time
                time = tm.time ()
                               
                try:
                    self.key = self.screen.get_wch ()
                except:
                    self.key = ''
                    
                self.screen.clear ()
                self.update (time - oldTime)   
                self.screen.refresh ()
                
                tm.sleep (1/50.)
                
        cs.wrapper (run)                                    # Start curses 'engine'
        
    def update (self, deltaT):                              # Note that update and draw are not synchronized
        self.deltaT = deltaT                                # Actual deltaT may vary, depending on processor load 

        if self.pause:                                      # If in paused state
            if self.key == space:
                self.pause = False                          #       Start playing
            elif self.key == enter:
                self.scoreboard.reset ()                    #       Reset score
            elif self.key == escape:
                self.exit ()                                #       End game
        else:                                               # Else, so if in active state
            for attribute in self.attributes:               #   Compute predicted values
                attribute.predict ()
                
            for attribute in self.attributes:               #   Correct values for bouncing and scoring
                attribute.interact ()
                
        for attribute in self.attributes:               #   Commit them to curses for display
            attribute.commit ()
            
    def scored (self, playerIndex):             # Player has scored
        self.scoreboard.increment (playerIndex) # Increment player's points
        self.serviceIndex = 1 - playerIndex     # Grant service to the unlucky player
        
        for paddle in self.paddles:             # Put paddles in rest position
            paddle.reset ()

        self.ball.reset ()                      # Put ball in rest position 
        self.pause = True                       # Wait for next round
        
    def draw (self, x, y, text):
        try:
            self.screen.addstr (
                int (self.heightInChars - y * self.heightInChars / orthoHeight),
                int (x * self.widthInChars / orthoWidth),
                text
            )
        except:
            pass
            
    def resize (self):
        self.heightInChars, self.widthInChars = self.screen.getmaxyx ()
        self.charWidthInOrtho = orthoWidth // self.widthInChars
        self.charHeightInOrtho = orthoHeight // self.heightInChars
        self.update (0)
        
game = Game ()  # Create and run game
