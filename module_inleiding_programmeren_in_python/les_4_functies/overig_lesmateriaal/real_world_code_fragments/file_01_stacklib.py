# ====== Global data

# --- Constants

locatorDim = 16
tagDim = 16
containerIdDim = 16
generalErrorTextDim = 256
reportListSize = 50
errorListSize = 50
maxPileHeight = 4
maxNrOfLocations = 2000
maxNrOfTags = 4000
maxNrOfJobsInQueue = 10
maxReasonableNumberOfAttemptsToGenerateUniqueNegativeContainerId = 1000 * (maxNrOfLocations + maxNrOfTags)

# --- Variables

# ... (Omitted)

# ====== Stack image management

# --- Initialisation and corrections

def initializeStackImages ():
    '''
    Actions:
        Fills actual stack image with initial data such: locator, type and ideal coordinates
        Calls predictStackimage to also fill predicted image
    '''


def correctStackImage (completeLocator, put, predicted = false):
    '''
    Actions:
        If completeLocator is flying
            Fills empty locations below locator with unknown containers from stackimage
            Report error

        If completeLocator is burried
            Remove containers above locator from stackimage
            Report error
    '''

# --- Displacements

def adminGet (completeSourceLocator, containerId, predicted = false):
    '''
    Actions:
        If source locator known
            If source locator occupied in stackimage
                If containerId parameter differs from containerId in stackimage
                    Report error

                Clear source locator
            Else
                Report error

            Call correctStackimage with parameter completeSourceLocator
        Else
            Report error

        Assign containerId parameter to spreader locator (P)

    Check uniqueness of id of picked up container

        If not predicted
            Call predictStackImage
    Remarks
        Error process will asynchroneously prompt crane driver for eventual unknown id's, spreader locator first
    '''

def adminPut (completeTargetLocator, predicted = false):
    '''
    Actions:
        If target locator known
            If target locator occupied in stackimage
                Report error
            Assign containerId from spreader (P) to target locator
            Call correctStackImage with parameter completeTargetLocator
        Else
            Assign containerId from spreader (P) to the unknown locator (U) (overwriting old entry)
            Report error

        If not predicted
            Call predictStackImage
    Remarks:
        If unknown locator filled, error process asks crane driver for the correct locator and call correctStackimage
    '''

def predictStackImage ():
    '''
    Actions:
        Copy actual stackimage to predicted stackimage
        Call adminGet and adminPut for each element of the job queue, virtual or not
    '''

# --- Searching the stack image

def partsFromLocator (locator):
    '''
    Actions:
        Split locator into parts
        Return parts
    '''

def locatorFromParts (parts):
    '''
    Actions:
        Contruct locator from parts
        Return locator
    '''

def upperLocatorFromPartialLocator (partialLocator, occupied, predicted = false):
    '''
    Actions:
        Search for most elevated occupied or non-occupied complete locator that matches partial locator
        If success
            Return found locator
        Else
            Return unknown locator (U)
    '''

def findNextDuplicateContainerId (referenceLocator, predicted = false):
    # ... To be called after tag detection, once this works
    '''
    Actions:
        If next locator with same containerId found
            Return it
        Else
            Return unknown locator (U)
    Remark:
        First call with duplicateLocator set equal to referenceLocator
        Sequence of calls finished if duplicatielocator returns reference locator.
    '''

def locatorFromContainerId (containerId, predicted = false):
    '''
    Actions:
        Search search predicted or actual stackimage, including spreader, for containerId, returning locator
        Return unknown locator (U) upon failure
    '''

def containerIdFromLocator (locator, predicted = false):
    '''
    Actions:
        Search predicted or actual stackimage, including spreader, for locator, returning containerId
        Negative (unknown) id's are unique and are returned by this function just as normal, positive id's
        Any occupied place in the stack has a nonzero containerId
        Returns empty containerId (0) if locator designates empty space
    '''

def locatorFromCoordinates (coordinates, useActualCoords = false, predicted = false):
    '''
    Actions:
        Convert XYZ coordinates in mm to locator
        If success
            Return conversion result
        Else
            Return unknown locator (U)
    '''

def coordinatesFromLocator (locator, useActualCoords = false, predicted = false):
    '''
    Actions:
        Convert locator to XYZ coordinates
        If success
            Return conversion result
        Else
            Returns unknown coordinates (-1, -1, -1)
    '''

def partialLocatorFromCoordinates (partialCoordinates, rtsAsStorage = false, useActualCoords = false, predicted = false):
    '''
    Actions:
        Convert XY coordinates in mm to partial locator
        If success
            Return conversion result
        Else
            Return unknown locator (U)
    '''

def coordinatesFromPartialLocator (partialLocator, useActualCoords = false, predicted = false):
    '''
    Actions:
        Convert partial locator to XY coordinates
        If success
            Return conversion result
        Else
            Returns unknown coordinates (-1, -1, -1)
    '''

def locationIndexFromLocator (completeLocator):
    '''
    Actions:
        If locator exists
            Return its loctation index
        Else
            Return -1
    '''

# ====== Tag table management

def tagFromContainerId (containerId):
    '''
    Actions:
        Search tagtable for containerId
        If found
            Return tag
        Else
            Return invalid tag ("")
    '''

def containerIdFromTag (tag):
    '''
    Actions:
        Search tagtable for tag
        If found
            Return containerId from tagtable
        Else
            Generate unique negative containerId
            Store tag with new containerId in tagtable
            Return new containerId
    '''

def changeContainerIdOfTag (tag, newContainerId):
    '''
    Actions:
        Remove existing pairs with newContainerId or tag from tagtable
        Insert new pair (tag, newContainerid)
    Remarks:
        Removing old occurences of newContainerId removes pair belonging to old, broken tag on same container
        Removing old occurences of tag removes pair belong to old, broken container from which tag was recycled
    '''

# ====== ContainerId management

def newUnknownContainerId ():
    '''
    Actions:
        Generates and returns random unique negative containerId
    Remarks:
        Searches stack AND TAGTABLE!!!
        Random generation makes O(n2) least painful, as it avoids clashes with constant average performance.
    '''

# ====== Job queue management

def eraseJob (job):
    '''
    Actions:
        Set source and target location type of job to ltNone
    '''

def insertJobAtIndex (job, index):
    '''
        If index too large or negative, job is inserted as last
    '''

def deleteJobFromIndex (index):
    '''
        If index too large or negative, last job is deleted
    '''

def advanceJobQueue ():
    '''
    Actions:
        Advance items in jobqueue towards low indexes
        Element 0 (pending) is discarded
        If queue empty afterwards
            Return false
        Else
            Return true

        Call predictStackImage
    '''

def clearJobQueue (includePending = true):
    '''
    Actions:
        Clear job queue

        If not predicted
            Call predictStackImage
    '''

# ====== Request management

def scheduleMoveRequest (partialFromLoc, partialToLoc, jobQueueIndex, isVirtual):
    '''
    Actions:
        Complete locators
        Construct job
        Call insertJobAtIndex with parameter jobQueueIndex
    Remarks:
        No check on containerId, to maintain parallel with manual control and independence of stack administration
        Virtual moves queued like any other, sequence control driver reacts differently enables mixing real and virtual moves
        To the predicted stackimage, any move request is issued asif it were virtual
    '''

def requestResetSequenceControl ():
    '''
    Actions:
        Clears job queue
        Reset sequence control
    '''

def requestResumeSequenceControl ():
    '''
    Actions:
        Clears job queue
        Put sequence control into active mode
    '''

# ====== Sequence control transfer functions

# --- Passing requests to sequence control

def queryMoveRequest ():
    '''
    Actions:
    If pending empty and queue nonempty
            Pass one movement command from queue to pending
            If it's virtual
                Call adminGet with containerId taken from stackImage
                Call adminPut
                Erase pending
                Return false
            Else
                Convert locators of pending job to coordinates in mm
                Put command in request-mailbox
                Return true
    Remarks:
        First deal with other requests, e.g. reset and resume, before querying a move request
    '''

# --- Notifying twistlock status changes

def notifyGet (coordinates, tag):
    '''
    Actions:
        Call locatorFromCoordinates to obtain source locator (maybe unknown)

        If tag valid
            Call containerIdFromTag
            Use containerId from tag
        Else
            Report error
            If locator known
                If locator occupied in stackimage
                    Use containerId from stackimage
                Else
                    Use new temporary containerId
            Else
                Use new temporary containerId

        Call adminGet (maybe with unknown locator)

    Remarks:
        Activated when twistlocs are being closed
        No need to search for duplicates of newly generated negative id, because its required to be unique by definition
    '''

def notifyPut (coordinates):
    '''
    Actions:
        Call locatorFromCoordinates to obtain target locator (maybe unknown)
        Call adminPut (maybe with unknown locator)

        Erase pending
    Remarks:
        Activated when twistlocs are being opened
        Pending command also destroyed in manual mode, no problem, destroyed anyhow
    '''

# ====== Reporting and error handling

# --- Reporting

def newReport (report):
    '''
    Actions:
        Adds new report to report list with incremented error version
    '''

# --- Error handling

def newError (error):
    '''
    Actions:
        Adds new error to error list with incremented error version
    '''

def newGeneralError (code, text):
    '''
    Actions:
        Adds new general error to error list with incremented error version
    '''

# ====== Process cooperation primitives

def continueProcessing ():
    '''
    Actions:
        If the controller wants the application's parts to continue processing
            Return true
        Else
            Return false
    Remarks:
        This function accesses the state-memory without guard of a semaphore
        as it reads and is not bothered by transient memory states.
        It does not bump priority but still may be called from a low priority thread,
        as it doesn't hold up other threads by claiming a semaphore.
        be called under low priority
        Applications can use this function as follows:
        (Win32 GUI)
        - Query it in the main windows message loop
        - Query it, triggered by a timer
        (Win32 Console or Daemon)
        - Query it in the main proprietary loop
    '''

# --- State memory and concurrency management

def createState ():
    '''
    Actions:
        Creates new state memory and semaphore
    '''

def openState ():
    '''
    Actions:
        Opens existing state memory and semaphore
    '''

def closeState ():
    '''
    Actions:
        Closes existing state memory and semaphore
    Remarks:
        State memory and semaphore are automatically discarded after last close
    '''

def hurryLogist ():
    '''
    Actions:
        Switch to priority time critical
    '''

def relaxLogist ():
    '''
    Actions:
        Switch to priority ordinary
    '''

def requestState ():
    '''
    Actions:
        Request access to state, uses counter to coagulate multiple requests to one
    '''

def releaseState ():
    '''
    Actions:
        Release access to state, uses counter to coagulate multiple releases to one
    '''

def hurryAndRequestState ():
    '''
    Actions:
        Call hurryLogist
        Call requestState
    '''

def releaseStateAndRelax ():
    '''
    Actions
        Call releaseState
        Call relaxLogist
    '''

# --- State versioning

def versionChanged (sharedVersion, localVersion):
    '''
    Actions:
        If sharedVersion exceeds localVersion
            Make localVersion equal to sharedVersion
            Return true
        Else
            Return false
    '''

# ====== Cooperation with SoftPlc

# --- Communication with SoftPlc

def callInitPlc ():
    '''
    Actions:
        Open shared memory of SoftPlc by call to initPlc
    Remarks:
        Function initPlc is only directly callable from within stackLib.cpp.
        By wrapping it into callInitPlc, it can be called indirectly by any user of stackLib.
    '''
