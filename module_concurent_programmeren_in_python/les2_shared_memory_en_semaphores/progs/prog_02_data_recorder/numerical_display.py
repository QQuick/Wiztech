import time as tm

import data_recorder as dr

with dr.DataRecorder () as dataRecorder:
    while True:
        for record in dataRecorder.readRecords (20):
            dataRecorder.printRecord (record)
        print ()
        tm.sleep (3)
