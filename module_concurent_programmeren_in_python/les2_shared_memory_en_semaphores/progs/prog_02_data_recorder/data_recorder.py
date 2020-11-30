import multiprocessing.shared_memory as sm
import numpy as np

import data_definition as dd

augmentedRingbufferSize = dd.ringbufferSize + 1    # One extra 'record' at end to store current index

class ReadbufferTooLargeError (Exception):
    def __init__ (self, readBufferSize):
        super () .__init__ ('ERROR: Size of readbuffer ({readbufferSize} > size of ringbuffer ({ringbufferSize})')

class DataRecorder:
    def __init__ (self, create = False, name = 'data_recorder'):
        self.create = create
        self.sharedMemoryName = name + '.shm'

    def __enter__ (self):
        self.ringbufferMemory = (
                sm.SharedMemory (   # Create shared memory
                    name = self.sharedMemoryName,
                    create = True,
                    size = augmentedRingbufferSize * dd.Record.itemsize
                )
            if self.create else
                sm.SharedMemory (   # Open shared memory
                    name = self.sharedMemoryName
                )
        )

        self.ringbuffer = np.ndarray (              # Define ringbuffer in shared memory
            shape = (augmentedRingbufferSize,),
            dtype = dd.Record,
            buffer = self.ringbufferMemory.buf
        )
        
        return self
        
    def __exit__ (self, *args):
        self.ringbufferMemory.close()
        
        if self.create:
            self.ringbufferMemory.unlink()
        
    def printRecord (self, measurement):
        print ('\t'.join ([
                f'{dd.fieldLabels [fieldIndex]}: {measurement [fieldIndex] : 7.2f}\t'
            for fieldIndex in range (0, dd.nrOfFields)
        ]))

    def writeRecord (self, record):        
        self.ringbuffer [int (self.ringbuffer [dd.ringbufferSize][0])] = record
        self.ringbuffer [dd.ringbufferSize][0] = (self.ringbuffer [dd.ringbufferSize][0] + 1) % dd.ringbufferSize
            
    def readRecords (self, readbufferSize):
        if readbufferSize <= dd.ringbufferSize:
            readbuffer = self.ringbuffer [  # Deliberately lag behind one sample to avoid reading halfwritten values
                int (self.ringbuffer [dd.ringbufferSize][0]) - readbufferSize:
                int (self.ringbuffer [dd.ringbufferSize][0])
            ]
            
            return readbuffer
        else:
            raise ReadbufferTooLargeError (readbufferSize)


            
