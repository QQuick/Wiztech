#define warnFloatIntRound 4244
#define warnDoubleFloatRound 4305

#pragma warning (disable: warnFloatIntRound warnDoubleFloatRound)

#include <ioStream.h>
#include <math.h>
#include <windows.h>

#ifdef IN
   #undef IN
#endif

#ifdef OUT
   #undef OUT
#endif

#if !(defined greenPlc || defined yellowPlc || defined bluePlc || defined redPlc)
   #include "color.plc"
#endif

#if !(defined greenPlc || defined yellowPlc || defined bluePlc || defined redPlc)
   #define greenPlc
#endif

#ifdef greenPlc
   #define plcMutex gPlcMutex
   #define pPlc pGPlc
   #define plc gPlc
   #define gPlc (*pGPlc)
   #define pMasterClock pGMasterClock
   #define store "gStore"
   #define TControl TGControl
   #define cleanUp gCleanup
   #define initPlc gInitPlc
   #define request gRequest
   #define release gRelease
   #define hurry gHurry
   #define relax gRelax
   #define hurryAndRequest gHurryAndRequest
   #define releaseAndRelax gReleaseAndRelax
#endif
#ifdef yellowPlc
   #define plcMutex yPlcMutex
   #define pPlc pYPlc
   #define plc yPlc
   #define yPlc (*pYPlc)
   #define pMasterClock pYMasterClock
   #define store "yStore"
   #define TControl TYControl
   #define cleanUp yCleanup
   #define initPlc yInitPlc
   #define request yRequest
   #define release yRelease
   #define hurry yHurry
   #define relax yRelax
   #define hurryAndRequest yHurryAndRequest
   #define releaseAndRelax yReleaseAndRelax
#endif
#ifdef bluePlc
   #define plcMutex bPlcMutex
   #define pPlc pBPlc
   #define plc bPlc
   #define bPlc (*pBPlc)
   #define pMasterClock pBMasterClock
   #define store "bStore"
   #define TControl TBControl
   #define cleanUp bCleanup
   #define initPlc bInitPlc
   #define request bRequest
   #define release bRelease
   #define hurry bHurry
   #define relax bRelax
   #define hurryAndRequest bHurryAndRequest
   #define releaseAndRelax bReleaseAndRelax
#endif
#ifdef redPlc
   #define plcMutex rPlcMutex
   #define pPlc pRPlc
   #define plc rPlc
   #define rPlc (*pRPlc)
   #define pMasterClock pRMasterClock
   #define store "rStore"
   #define TControl TRControl
   #define cleanUp rCleanup
   #define initPlc rInitPlc
   #define request rRequest
   #define release rRelease
   #define hurry rHurry
   #define relax rRelax
   #define hurryAndRequest rHurryAndRequest
   #define releaseAndRelax rReleaseAndRelax
#endif

#define storeMem "sharedMem_control_"store
#define storeSem "mutexSem_control_"store

#if defined defPlc || defined usePlc || defined simPlc
#include "dVarSelf.h"
#endif

#ifdef seePlc
#include "dVarDesc.h"
#endif

// Debugging

#ifdef simPlc
void trace (int i) {
   if (boolContext [boolLevel])
      cout << i << ' ';
}
#endif

// General reserved words

#ifdef simPlc

#define false FALSE
#define true TRUE

#define and &&
#define not !
#define or ||

#define hour * 3600
#ifdef min
   #undef min
#endif
#define min * 60
#define sec
#define msec / 1000

// Reserved words for modularisation

#define UNIT /##/

#define PROC double
#define FUNC
#define RESULT if (boolContext [boolLevel]) functionResult [blockLevel] =
#define BLOCK { blockLevel++;
#define ENDBLOCK return functionResult [blockLevel--]; }

#define WRITE &
#define READ

// Reserved words for contructing IF statements

#define IF _if (
#define THEN );
#define ELSIF _elsif (
#define ELSE _else ();
#define ENDIF _endif ();

// Reserved words for _constructing SELECT statements

#define SELECT _select (
#define FROM );
#define IS _is (
#define DO );
#define ENDSEL _endsel ();

// Reserved words for _construction FOR statements

#define FOR     {int forCount, &
#define RANGE   = forCount, forStart =
#define TO      , forStep = 1, forEnd = 1 +
#define DOWNTO  , forStep = -1, forEnd = -1 +
#define PERFORM \
   ; for (forCount = forStart; forCount != forEnd; forCount += forStep) {
#define ENDFOR }}

// Reserved words for operating PLC program elements

#define act _act ()
#define lat _lat ()
#define unl _unl ()
#define one _one ()
#define res _res ()
#define inc _inc ()
#define dec _dec ()

#endif

//____________________

class TControl;

#if defined defPlc || defined simPlc || defined seePlc
   HANDLE plcMutex = 0;
   TControl *pPlc = NULL;
#endif

#if defined defPlc || defined simPlc || defined seePlc
   double *pMasterClock = NULL;
#endif

#ifdef usePlc
   extern HANDLE plcMutex;
   extern TControl *pPlc;
   extern double *pMasterClock;
#endif

//____________________

#define _noAssign(T)						\
   void operator = (T &t) {			\
      fail ("Illegal assignment");	\
   }

#define _nonPlcAssign(T)		\
   void operator = (T val) {	\
      if (!lock)					\
         this->val = val;		\
   }

#define _construct(T1, T2)													\
	T1 () {}             /* For ordinary definitions */			\
	T1 (T2 val) {        /* To pass value parameters */			\
		this->val = val;														\
	}																				\
	void _init (T2 val) {													\
		this->val = val;	/* To initialize PAR's and TIMER's */	\
	}

#define _brackets(T)				\
   T &operator [] (int i) {	\
      return this [i];			\
   }

//____________________

class INPUT {

public:

#ifdef simPlc
   _construct (INPUT, int)
   _brackets (INPUT)
   void operator = (int val) {
      if (!lock && boolContext [boolLevel])
         INPUT::val = val;
   }
   int operator << (int val) {
      lock = TRUE;
	   INPUT::val = val;
      return val;
   }
#endif

#if !defined simPlc && !defined seePlc
	_nonPlcAssign (int)
#endif

#ifndef seePlc
   operator int () {return val;}
#endif

#ifdef seePlc
public:
#else
protected:
#endif

   int val;
   int lock;

};

//____________________

class MARKER: public INPUT {

public:

#ifdef simPlc
   _construct (MARKER, int)
   _brackets (MARKER)
   _noAssign (MARKER)
   void _act () {
      if (!lock)
         val = boolContext [boolLevel];
   }
#endif

};

//____________________

class LATCH: public INPUT {

public:

#ifdef simPlc
	_construct (LATCH, int)
   _brackets (LATCH)
   _noAssign (LATCH)
   void _lat () {
      if (!lock && boolContext [boolLevel])
         val = TRUE;
   }
   void _unl () {
      if (!lock && boolContext [boolLevel])
         val = FALSE;
   }
#endif

};

//____________________

class ONESHOT: public INPUT {

public:

#ifdef simPlc
   _construct (ONESHOT, int)
   _brackets (ONESHOT)
   _noAssign (ONESHOT)
   void _one () {
      if (!lock)
         val = boolContext [boolLevel] && !oldContext;
      oldContext = boolContext [boolLevel];
   }
#endif

#ifdef simPlc
private:
#else
public:
#endif

   int oldContext;

};

//____________________

template <class T>
class ordinalT {

public:

#ifdef simPlc
   _construct (ordinalT, T)
   _brackets (ordinalT <T>)
   void operator = (T t) {
      if (!lock && boolContext [boolLevel])
	 val = t;
   }
   void operator = (ordinalT <T> o) {
      *this = o.val;
   }
   T operator << (T val) {
      lock = TRUE;
      ordinalT <T> ::val = val;
      return val;
   }
#endif

#if !defined simPlc && !defined seePlc
	_nonPlcAssign (T)
#endif

#ifndef seePlc
   operator T () {return val;}
#endif

#ifdef seePlc
   friend ostream &operator << (ostream &os, ordinalT <T> &o);
   friend istream &operator >> (istream &is, ordinalT <T> &o);
#endif

#ifdef simPlc
protected:
#else
public:
#endif

   T val;
   int lock;

};

//____________________

typedef ordinalT <int> INTEGER;
typedef ordinalT <unsigned int> NATURAL;
typedef ordinalT <float> REAL;

//____________________

class TIMER: public ordinalT <double> {

public:

#ifdef simPlc
	TIMER () {}
	TIMER (double val) {
		this->val = *pMasterClock - val;
	}
	void _init (double val) {
		this->val = *pMasterClock = val;
	}
   _brackets (TIMER)
   _noAssign (TIMER)
   double operator << (double val) {
      lock = TRUE;
      TIMER::val = val;
      return val;
   }
   void _res () {
      if (!lock && boolContext [boolLevel])
         val = *pMasterClock;
   }
#endif

#if !defined simPlc && !defined seePlc
   void operator = (double val) {
      if (!lock)
         this->val = *pMasterClock - val;
   }
#endif

#ifndef seePlc
   operator double () {
      if (lock)
         return val;
   else
         return *pMasterClock - val;
   }
#endif

};

//____________________

template <class T>
class enumT: public ordinalT <T> {

public:

#ifdef simPlc
	_construct (enumT <T>, T)
	enumT <T> (int val) {
		this->val = T (val);
	}
   _brackets (enumT <T>)
   void _inc () {
      if (!lock && boolContext [boolLevel])
	 val = T (val + 1);
   }
   void _dec () {
      if (!lock && boolContext [boolLevel])
	 val = T (val - 1);
   }
#endif

#if defined simPlc || !defined seePlc
   void operator = (T val) {(* (ordinalT <T> *) this) = val;}
   void operator = (int val) {*this = T (val);}
#endif

#if defined defPlc || defined usePlc
   operator T () {  // !!! Helpt niet
      return val;
   }
#endif

};

//____________________

#ifndef seePlc

class TControl {

#pragma pack(1)  // Force same alignment in simPlc, seePlc and other users of plc-variables

public:
   double masterClock;

#ifdef undefined  // !!! Obsolete using nmake, 15/7/97, but possibly usable with MS project manager
   #if defined comPlc
      #if defined greenPlc
         #include "green.tem"
      #elif defined yellowPlc
         #include "yellow.tem"
      #elif defined bluePlc
         #include "blue.tem"
      #elif defined redPlc
         #include "red.tem"
      #endif
   #else
      #include "vars.plc"  // PLC variable definitions
   #endif
#endif

#include "vars.plc"  // PLC variable definitions  !!! Added 15/7/97

#ifdef simPlc
   static TControl *makeNew ();
   void init ();
   void sweep();
   #include "blocks.plc"
#endif

#pragma pack()

};

#endif

/* Removed 17/12/1999, OS2 relict
//____________________

#if defined defPlc || defined simPlc || defined seePlc
void APIENTRY cleanUp () {
   WaitForSingleObject (plcMutex, INFINITE);
   ReleaseMutex (plcMutex);
   ReleaseMutex (plcMutex);
   CloseHandle (plcMutex);
}
#endif
*/

//____________________

#if defined defPlc || defined seePlc
void initPlc () {
   SetPriorityClass (GetCurrentProcess (), NORMAL_PRIORITY_CLASS);
   SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_NORMAL);

   plcMutex = OpenMutex (MUTEX_ALL_ACCESS, FALSE, storeSem);

   HANDLE mapObject = OpenFileMapping (
      FILE_MAP_READ | FILE_MAP_WRITE,
      FALSE,
      storeMem
   );

   * (void**) &pPlc = MapViewOfFile (
      mapObject,
      FILE_MAP_READ | FILE_MAP_WRITE,
      0,
      0,
      0
   );

   pMasterClock = (double*) pPlc;
}
#endif

//____________________

#if defined defPlc || defined seePlc

void hurry () {
   SetPriorityClass (GetCurrentProcess (), REALTIME_PRIORITY_CLASS);
   SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_TIME_CRITICAL);
};

void relax () {
   SetPriorityClass (GetCurrentProcess (), NORMAL_PRIORITY_CLASS);
   SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_NORMAL);
};

void request () {
   WaitForSingleObject (plcMutex, INFINITE);
};

void release () {
   ReleaseMutex (plcMutex);
};

void hurryAndRequest () {
   hurry ();
   request ();
}

void releaseAndRelax () {
   release ();
   relax ();
}

#endif

#ifdef usePlc
extern void hurry ();
extern void relax ();
extern void request ();
extern void release ();
extern void hurryAndRequest ();
extern void releaseAndRelax ();
#endif
