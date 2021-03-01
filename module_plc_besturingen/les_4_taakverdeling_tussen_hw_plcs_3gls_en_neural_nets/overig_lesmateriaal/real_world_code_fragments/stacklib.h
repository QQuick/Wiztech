// ******************** Defines

#define dataDir "c:\\bor_nt\\dat"

#define stateMem (*pStateMem)
#define sm stateMem
#define as (sm.actualStackImage)
#define ps (sm.predictedStackImage)
#define tt (sm.tagTable)
#define jq (sm.jobQueue)
#define rq (sm.request)
#define rl (sm.reportList)
#define el (sm.errorList)

// ******************** Includes

#include "simPlc.h"  // Include types TBaseREQUEST, TBaseREPORT, TBaseFAULT via vars.plc of high level control
#include <windows.h>

// ******************** Standard typed constants 

const int
	locatorDim = 16,
	tagDim = 16,
	sContainerIdDim = 16,
	generalErrorTextDim = 256,
	reportListSize = 50,
	errorListSize = 50,
	maxPileHeight = 4,
	maxNrOfLocations = 2000,
	maxNrOfTags = 4000,
	maxNrOfJobsInQueue = 10,
	maxReasonableNumberOfAttemptsToGenerateUniqueNegativeContainerId =
		1000 * (maxNrOfLocations + maxNrOfTags);

// ******************** Types and non-standard typed constants

typedef __int64 TVersion;
typedef char TTag [tagDim];	// "" denotes invalid tag
typedef int TContainerId;
typedef char TSContainerId [sContainerIdDim];

struct TTagRecord {
	TTag tag;
	TContainerId containerId;
};

typedef TTagRecord TTagRecords [maxNrOfTags];

struct TTagTable {	// May contain "holes" to avoid sorting.
							// Sorting with linear search has relatively low payoff.
	TVersion version;
	TTagRecords tagRecords;
};

enum TLocationType {
	ltNone     = 'N',
	ltStack    = 'S',
	ltRts      = 'R',
	ltTilt     = 'T',
	ltBulk     = 'B',
	ltSpreader = 'P',
	ltImport   = 'I',
	ltExport   = 'E',
	ltUnknown  = 'U'
};

struct TLocatorParts {
	char chTypePart;
	int iXPart;
	char chYPart;
	int iZPart;
};

typedef char TLocator [locatorDim];

struct TCoordinates {
	float
		x,
		y,
		z;
};

typedef float TWeight;

struct TLocation {  // No canonical form in RAM cache, to vulnerable without transaction support on the cache!
						  // Driver for a database with transaction support may "canonize" by separating container
						  // data from location data and by leaving out the part labeled "fixed data".
   // Fixed data
	TLocator locator;
	TCoordinates idealCoordinates;
	// Varying data
	TContainerId containerId;
	TCoordinates actualCoordinates;
	TWeight weight;
};

typedef TLocation TLocations [maxNrOfLocations];  // No "precooked" geometric interpretation in array indexing

struct TStackImage {
	TVersion version;
	TLocations locations;
};

struct TJob {
	TLocator fromLocator;
	TLocator toLocator;
	bool isVirtual;
};

typedef TJob TJobs [maxNrOfJobsInQueue];  // Jobs [0] denotes pending job

struct TJobQueue {  // No index: maximum robustness
	TVersion version;
	TJobs jobs;
};

enum TGeneralRequestCode {
	grqNone
};

struct TRequest {
	TVersion version;
	TControl::TBaseREQUEST softPlcRequestCode;
	TCoordinates
		fromCoordinates,
		toCoordinates;
	TGeneralRequestCode generalRequestCode;

};

enum TGeneralReportCode {
	grpNone
};

struct TReport {
	TVersion version;
	TControl::TBaseREPORT softPlcReportCode;
	TCoordinates transferCoordinates;
	TGeneralReportCode generalReportCode;
};

typedef TReport TReportList [reportListSize];

enum TGeneralErrorCode {
	geNone,
	geStackImage
};

typedef char TGeneralErrorText [generalErrorTextDim];

struct TError {
	TVersion version;
	TControl::TBaseFAULT softPlcFaultCode;
	TGeneralErrorCode generalErrorCode;
	TGeneralErrorText generalErrorText;
};

typedef TError TErrorList [errorListSize];

struct TStateMem {
	// Persistent data
	TStackImage actualStackImage;
	TTagTable tagTable;
	TJobQueue jobQueue;  // Pending is just another queue entry
	// Volatile data
	TStackImage predictedStackImage;
	TCoordinates currentSpreaderCoordinates;  // To fast-changing to make versioning attractive
	bool twistLocked;  // To simple to make versioning attractive
							 // don't use get/put, must also work in manual control!!!
	TRequest request;
	TReportList reportList;
	TErrorList errorList;
	bool continueProcessing;
};

typedef HANDLE TStateMap;
typedef HANDLE TStateSem;

// ******************** Variable declarations

//	====== State memory management

extern TStateMem *pStateMem;
extern TStateSem stateSem;
extern int stateSemCount;

// ******************** Function prototypes

// ====== Stack image management

// --- Initialisation and corrections

void initializeStackImages ();
/*
Actions:
	Fills actual stack image with initial data such: locator, type and ideal coordinates
	Calls predictStackimage to also fill predicted image
*/

void correctStackImage (TLocator completeLocator, bool put, bool predicted = false);
/*
Actions:
	If completeLocator is flying
		Fills empty locations below locator with unknown containers from stackimage
		Report error

	If completeLocator is burried
		Remove containers above locator from stackimage
		Report error
*/

// --- Displacements

void adminGet (TLocator completeSourceLocator, TContainerId containerId, bool predicted = false);
/*
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
*/

void adminPut (TLocator completeTargetLocator, bool predicted = false);
/*
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
*/

void predictStackImage ();
/*
Actions:
	Copy actual stackimage to predicted stackimage
	Call adminGet and adminPut for each element of the job queue, virtual or not
*/

// --- Searching the stack image

void partsFromLocator (TLocatorParts &parts, TLocator locator);
/*
Actions:
	Spits locator into parts
*/

void locatorFromParts (TLocator &locator, TLocatorParts parts);
/*
Actions:
	Contructs locator from parts
*/

void upperLocatorFromPartialLocator (TLocator &upperLocator, TLocator partialLocator, bool occupied, bool predicted = false);
/*
Actions:
	Search for most elevated occupied or non-occupied complete locator that matches partial locator
	If success
		Return found locator
	Else
		Return unknown locator (U)
*/

void findNextDupplicateContainerId (TLocator &dupplicateLocator, TLocator referenceLocator, bool predicted = false);
// ... To be called after tag detection, once this works
/*
Actions:
	If next locator with same containerId found
		Return it
	Else
		Return unknown locator (U)
Remark:
	First call with dupplicateLocator set equal to referenceLocator
	Sequence of calls finished if dupplicatielocator returns reference locator.
*/

void locatorFromContainerId (TLocator &locator, TContainerId containerId, bool predicted = false);
/*
Actions:
	Search search predicted or actual stackimage, including spreader, for containerId, returning locator
	Return unknown locator (U) upon failure
*/

void containerIdFromLocator (TContainerId &containerId, TLocator locator, bool predicted = false);
/*
Actions:
	Search predicted or actual stackimage, including spreader, for locator, returning containerId
	Negative (unknown) id's are unique and are returned by this function just as normal, positive id's
	Any occupied place in the stack has a nonzero containerId
	Returns empty containerId (0) if locator designates empty space
*/

void locatorFromCoordinates (
	TLocator &locator, 
	TCoordinates coordinates, 
	bool useActualCoords = false,
	bool predicted = false
);
/*
Actions:
	Convert XYZ coordinates in mm to locator
	If success
		Return conversion result
	Else
		Return unknown locator (U)
*/

void coordinatesFromLocator (
	TCoordinates &coordinates, 
	TLocator locator,
	bool useActualCoords = false,
	bool predicted = false
);
/*
Actions:
	Convert locator to XYZ coordinates
	If success
		Return conversion result
	Else
		Returns unknown coordinates (-1, -1, -1)
*/

void partialLocatorFromCoordinates (
	TLocator &partialLocator,
	TCoordinates partialCoordinates,
	bool rtsAsStorage = false,
	bool useActualCoords = false,
	bool predicted = false
);

/*
Actions:
	Convert XY coordinates in mm to partial locator
	If success
		Return conversion result
	Else
		Return unknown locator (U)
*/

void coordinatesFromPartialLocator (
	TCoordinates &partialCoordinates, 
	TLocator partialLocator, 
	bool useActualCoords = false, 
	bool predicted = false
);
/*
Actions:
	Convert partial locator to XY coordinates
	If success
		Return conversion result
	Else
		Returns unknown coordinates (-1, -1, -1)
*/

int getLocationIndex (TLocator completeLocator);
/*
Actions:
	If locator exists
		Return its loctation index
	Else
		Return -1
*/

// ====== Tag table management

void tagFromContainerId (TTag &tag, TContainerId containerId);
/*
Actions:
	Search tagtable for containerId
	If found
		Return tag
	Else
		Return invalid tag ("")
*/

void containerIdFromTag (TContainerId &containerId, TTag tag);
/*
Actions:
	Search tagtable for tag
	If found
		Return containerId from tagtable
	Else
		Generate unique negative containerId
		Store tag with new containerId in tagtable
		Return new containerId
*/

void changeContainerIdOfTag (TTag tag, TContainerId newContainerId);
/*
Actions:
	Remove existing pairs with newContainerId or tag from tagtable
	Insert new pair (tag, newContainerid)
Remarks:
	Removing old occurences of newContainerId removes pair belonging to old, broken tag on same container
	Removing old occurences of tag removes pair belong to old, broken container from which tag was recycled
*/

// ====== ContainerId management

int getNewUnknownContainerId ();
/*
Actions:
	Generates random unique negative containerId
Remarks:
	Searches stack AND TAGTABLE!!!
	Random generation makes O(n2) least painful, as it avoids clashes with constant average performance.
*/

// ====== Job queue management

void eraseJob (TJob &job);
/*
Actions:
	Set source and target location type of job to ltNone
*/

void insertJobAtIndex (TJob job, int index);
/*
	If index too large or negative, job is inserted as last
*/

void deleteJobFromIndex (int index);
/*
	If index too large or negative, last job is deleted
*/

bool advanceJobQueue ();
/*
Actions:
	Advance items in jobqueue towards low indexes
	Element 0 (pending) is discarded
	If queue empty afterwards
		Return false
	Else
		Return true

	Call predictStackImage
*/

void clearJobQueue (bool includePending = true);
/*
Actions:
	Clear job queue

	If not predicted
		Call predictStackImage
*/

// ====== Request management

void scheduleMoveRequest (TLocator partialFromLoc, TLocator partialToLoc, int jobQueueIndex, bool isVirtual);
/*
Actions:
	Complete locators
	Construct job
	Call insertJobAtIndex with parameter jobQueueIndex
Remarks;
	No check on containerId, to maintain parallel with manual control and independence of stack administration
	Virtual moves queued like any other, sequence control driver reacts differently enables mixing real and virtual moves
	To the predicted stackimage, any move request is issued asif it were virtual
*/

void requestResetSequenceControl ();
/*
Actions:
	Clears job queue
	Reset sequence control
*/

void requestResumeSequenceControl ();
/*
Actions:
	Clears job queue
	Put sequence control into active mode
*/

// ====== Sequence control transfer functions

// --- Passing requests to sequence control

void queryMoveRequest ();
/*
Actions:
   If pending empty and queue nonempty
		Pass one movement command from queue to pending
		If it's virtual
			Call adminGet with containerId taken from stackImage
			Call adminPut
			Erase pending ();
			Return false
		Else
			Convert locators of pending job to coordinates in mm
			Put command in request-mailbox
			Return true
Remarks:
	First deal with other requests, e.g. reset and resume, before querying a move request
*/

// --- Notifying twistlock status changes

void notifyGet (TCoordinates coordinates, TTag tag);
/*
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
*/

void notifyPut (TCoordinates coordinates);
/*
Actions:
	Call locatorFromCoordinates to obtain target locator (maybe unknown)
	Call adminPut (maybe with unknown locator)

	Erase pending;
Remarks:
	Activated when twistlocs are being opened
	Pending command also destroyed in manual mode, no problem, destroyed anyhow
*/

// ====== Reporting and error handling

// --- Reporting

void newReport (TReport report);
/*
Actions:
	Adds new report to report list with incremented error version
*/


// --- Error handling

void newError (TError error);
/*
Actions:
	Adds new error to error list with incremented error version
*/

void newGeneralError (TGeneralErrorCode code, TGeneralErrorText text);
/*
Actions:
	Adds new general error to error list with incremented error version
*/

// ====== Process cooperation primitives

bool continueProcessing ();
/*
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
*/

// --- State memory and concurrency management

void createState ();
/*
Actions:
	Creates new state memory and semaphore
*/

void openState ();
/*
Actions:
	Opens existing state memory and semaphore
*/

void closeState ();
/*
Actions:
	Closes existing state memory and semaphore
Remarks:
	State memory and semaphore are automatically discarded after last close
*/

void hurryLogist ();
/*
Actions:
	Switch to priority time critical
*/

void relaxLogist ();
/*
Actions:
	Switch to priority ordinary
*/

void requestState ();
/*
Actions:
	Request access to state, uses counter to coagulate multiple requests to one
*/

void releaseState ();
/*
Actions:
	Release access to state, uses counter to coagulate multiple releases to one
*/

void hurryAndRequestState ();
/*
Actions:
	Call hurryLogist
	Call requestState
*/

void releaseStateAndRelax ();
/*
Actions
	Call releaseState
	Call relaxLogist
*/

// --- State versioning

bool versionChanged (TVersion sharedVersion, TVersion &localVersion);
/*
Actions:
	If sharedVersion exceeds localVersion
		Make localVersion equal to sharedVersion
		Return true
	Else
		Return false
*/

// ====== Cooperation with SoftPlc

// --- Communication with SoftPlc

void callInitPlc ();
/*
Actions:
	Open shared memory of SoftPlc by call to initPlc
Remarks:
	Function initPlc is only directly callable from within stackLib.cpp.
	By wrapping it into callInitPlc, it can be called indirectly by any user of stackLib.
*/

// ******************** Classes with in-line calls to global functions

class TStateGuard {  // Destructor forces matched release, so we don't forget...
public:
	TStateGuard () {requestState ();};
	~TStateGuard () {releaseState ();};
};
