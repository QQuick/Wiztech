bottom = -500

towerLeft = -600
towerRight = -200
towerAttic = 300

peakTop = 800
towerMiddle = (towerLeft + towerRight) // 2

drawRectangle (towerLeft, bottom, towerRight, towerAttic, True)
drawTriangle (towerLeft, towerAttic, towerMiddle, peakTop, towerRight, towerAttic, True)  
 
drawCircle (towerMiddle, towerAttic + 150, 50)
