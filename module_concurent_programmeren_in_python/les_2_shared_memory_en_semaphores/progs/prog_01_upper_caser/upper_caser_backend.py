import multiprocessing.shared_memory as sm
import time as tm

message = sm.ShareableList ((' ' * 256,), name = 'capitalizer')

while message [0]:
    message [0] = message [0] .upper ()
    tm.sleep (0.1)

message.shm.close ()
message.shm.unlink ()
