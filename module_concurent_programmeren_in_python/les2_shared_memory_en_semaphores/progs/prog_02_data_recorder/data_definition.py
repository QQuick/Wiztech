import numpy as np

Timestamp = np.float64  # Seconds
Quantity = np.float64   # Any physical quantity in high precision

fieldLabels = (
    'timestamp',
    'potential',
    'current'
)

nrOfFields = len (fieldLabels)

for fieldIndex, fieldLabel in enumerate (fieldLabels):
    globals ()[fieldLabel + 'Index'] = fieldIndex

Record = np.dtype ([
        (fieldLabels [fieldIndex],) + npTypeDescriptor
    for fieldIndex, npTypeDescriptor in enumerate ((
        (Timestamp,),
        (Quantity,),
        (Quantity,)
    ))
])

maxPotential = 40
maxCurrent = 20

ringbufferSize = 64
