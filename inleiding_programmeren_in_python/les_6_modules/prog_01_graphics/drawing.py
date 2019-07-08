import draw_lib as dl

bottom = -500

towerLeft = -600
towerRight = -200
towerAttic = 300
peakTop = 800

aisleRight = 600
aisleAttic = -100

roofRight = 400
roofTop = 100

towerWindowWidth = 40
aisleWindowWidth = 70

dl.drawRectangle (towerLeft, bottom, towerRight, towerAttic, True)
dl.drawTriangle (towerLeft, towerAttic, (towerLeft + towerRight) // 2, peakTop, towerRight, towerAttic, True)

dl.drawRectangle (towerRight, bottom, aisleRight, aisleAttic, True)
dl.drawLine (aisleRight, aisleAttic, roofRight, roofTop, True)
dl.drawLine (roofRight, roofTop, towerRight, roofTop, True)

towerMiddle = (towerLeft + towerRight) // 2

for towerWindowIndex in range (3):
    windowBottom = bottom + 100 + towerWindowIndex * 200
    dl.drawRectangle (towerMiddle - towerWindowWidth // 2, windowBottom, towerMiddle + towerWindowWidth // 2, windowBottom + 150)

for aisleWindowIndex in range (3):
    windowLeft = towerRight + 150 + aisleWindowIndex * 200
    dl.drawRectangle (windowLeft, bottom + 100, windowLeft + aisleWindowWidth, bottom + 300)
    
dl.drawCircle (towerMiddle, towerAttic + 150, 50)
    
horizon = bottom + 200
    
dl.drawLine (xMin, horizon, towerLeft, horizon)
dl.drawLine (aisleRight, horizon, xMax, horizon)

while True:
    pass

