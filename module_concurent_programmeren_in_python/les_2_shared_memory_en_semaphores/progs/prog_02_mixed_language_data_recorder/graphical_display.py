import time as tm

import data_recorder as dr
import data_definition as dd

with dr.DataRecorder () as dataRecorder:
    while True:
        record = dataRecorder.readRecords (1)[0]
        potentialString = ''.join ([
                'U' if potential == round (record [dd.potentialIndex]) else '|' if potential == 0 else ' '
            for potential in range (-dd.maxPotential, dd.maxPotential + 1)
        ])

        currentString = ''.join ([
                'I' if current == round (record [dd.currentIndex]) else '|' if current == 0 else ' '
            for current in range (-dd.maxCurrent, dd.maxCurrent + 1)
        ])
                
        print (f'{record [dd.timestampIndex] : 7.2f}          {potentialString}          {currentString}')

        tm.sleep (0.3)
