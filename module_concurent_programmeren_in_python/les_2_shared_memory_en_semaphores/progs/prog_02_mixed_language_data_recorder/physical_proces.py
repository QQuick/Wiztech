import time as tm
import math as mt

import data_recorder as dr
import data_definition as dd

startTime = tm.time ()
with dr.DataRecorder (True) as dataRecorder:
    while True:
        timestamp = tm.time () - startTime
        record = (  # Simulated data
            timestamp,
            dd.maxPotential * mt.sin (timestamp),
            dd.maxCurrent * mt.cos (timestamp)
        )
        
        dataRecorder.printRecord (record)
        dataRecorder.writeRecord (record)
        tm.sleep (0.15)
        
        
    

