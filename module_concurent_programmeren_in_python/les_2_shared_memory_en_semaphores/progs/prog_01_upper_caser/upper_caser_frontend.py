import multiprocessing.shared_memory as sm
import time as tm

message = sm.ShareableList (name = 'capitalizer')

while True:
    message [0] = input ('Geef boodschap in kleine letters ([Enter] to stop): ')
    tm.sleep (0.5)
    
    if not message [0]:
        break
    
    print ('De boodschap in hoofdletters is:', message [0])

message.shm.close ()
