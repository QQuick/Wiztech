/*
This is the main source module of program "channel"
Each instance of program "channel" represents one asynchroneous FDPU recording channel of type CH_STANDARD.
There may also be other channel types active, for example synchroneous interrupt driven channels, locked to external PLC sweeps.
Below, when referring to a channel, a channel of type CH_STANDARD is meant.
The amount of channels is limited by available memory and processor speed.

Channels can be started up from the command line. Example: Channel 3 is started up by the command "start /n /min channel.exe 3".

In the central configuration file the following parameters of each channel may be specified in this order:
- SLEEPTIME <#ms>     : How long a channel remains inactive between two adjacent samples,       default value 100.
- HISTORY   <#samples>: The number of samples recorded to disk before a trigger event, default value 0.
- FUTURE    <#samples>: The number of samples recorded to disk after a trigger event,  default value 0.
- FILESIZE  <#bytes>  : The maximum disk file size in bytes, default 1000000.
                        This size will be rounded down to the nearest multiple of the size of one snapshot (samplevector).
If a parameter including its keyword is skipped, the default value is assumed.

Each individual channel owns a shared memory area as does each driver.
A channel periodically gathers its data from the shared memory areas of active FDPU drivers.
It puts this so called "snapshot" into its channel shared memory, aligned according to the FDPU standard data format.
If a user interface needs to show real time data for a channel, it can obtain the data from the channel shared memory,
after having requested the semaphore belonging to this memory.

Each channel permanently maintains a ringbuffer of HISTORY + 1 + FUTURE snapshots.
If a channel is triggered, FUTURE snapshots are recorded after the trigger event.
After this, the whole ringbuffer is dumped to channels diskfile, which has also a cyclic strucure.
In the first 4 bytes of this diskfile a pointer is maintained to the first byte of the file that is to be overwritten by new data.

If new triggerevents keep occurring before the ringbuffer has a chance to refil to the normal level,
snapshots keep being written to disk permantently, until FUTURE samples pass without any new trigger events.
So a user interface can not search the disk file by skipping multiples of a ringbuffersize!
It should look for a new trigger event or search for a time gap that is an order of magnitude larger than the channel's SLEEPTIME.

The fact that a channel triggered is not written to disk.
User interface level trigger autonomously on individual variables to offer detailed information on what happened.
Channels edge trigger of whole groups of variables, using bitmasks for speed sake.
*/


// STANDARD DEFINES

#define INCL_DOSMEMMG
#define INCL_DOSPROCESS
#define INCL_DOSSEMAPHORES

// STANDARD INCLUDES

#include <ioStream.h>
#include <stdLib.h>

// APPLICATION INCLUDES

#include "chDisk.h"
#include "chCopier.h"
#include "chNames.h"
#include "chRegis.h"
#include "configFi.h"
#include "priority.h"
#include "sysRes.h"
#include "diction.h"

// VARIABLES

int
   nrOfPreSamples   =       0,  // Length of recorded history before trigger event
   nrOfPostSamples  =       0,  // Lenght of recorded future after trigger event
   nrOfSamples      =       0,  // To be computed in function readChannelParameters
   roughMaxFileSize = 1000000,  // Size of recording disk file
   sleepTime        =     100;  // ms


// FUNCTIONS

void readChannelParameters () {       // Read command line parameters of a channel
   configFile.open (configFileName);  // Closing done by destructor at program termination
   configFile >> configString;        // Read a symbol from the configureation file

   if (!strcmp (configString, "SLEEPTIME"))             //  Is the sleeptime specified?
      configFile >> sleepTime >> configString;          //  Read it

   if (!strcmp (configString, "HISTORY"))               //  Is the history size specified?
      configFile >> nrOfPreSamples >> configString;     //  Read it

   if (!strcmp (configString, "FUTURE"))                //  Is the future size specified?
      configFile >> nrOfPostSamples >> configString;    //  Read it

   if (!strcmp (configString, "FILESIZE"))              //  Is the circular disk file size specified?
      configFile >> roughMaxFileSize >> configString;   //  Read it

   nrOfSamples = nrOfPreSamples + nrOfPostSamples + 1;  //  Add 1 sample to account for the present snapshot
}


inline int next (int index) {           // Move index to next element of ringbuffer
   return  (index + 1) % nrOfSamples;   // Increment, then clip
}

// MAIN

void main (int argc, char *argv[]) {   // Initialisation + main channel loop
   TBool initialized = false;          // Channel not yet initialized
   int
      currentIndex = nrOfSamples - 1,  // Moves to next el. before sampling
      oldestIndex = 0,                 // Will be adapted before sampling
      oldestUnwrittenIndex = -1;       // No samples available that were not
                                       // yet written to disk

   setNames (argc, argv);                             // Accept channelname and construct derived names
   readChannelParameters ();                          // Read diverse channel settings
   registerAll ();                                    // Register which variables from which drivers
                                                      // should be recorded by this channel
   initDiskRing (roughMaxFileSize, snapshotMemSize);  // Initialize disk ring buffer
   hurry ();                                          // Switch to priority timecritical

   // Allocate channelmemory
   TSharedMemBox channelMemBox (channelMemName, snapshotMemSize);  // Create the memory and it's semaphores
   void *pChannelMem = channelMemBox;                              // Get a pointer to the memory

   // Allocate snapshot ring buffer
   int snapRingMemSize = nrOfSamples * snapshotMemSize;            // Compute required size of ringbuffer
   TPrivateMemBox snapRingMemBox (snapRingMemSize);                // Allocate it as private memory
   void *pSnapRingMem = snapRingMemBox;                            // Get a pointer to it
   memset (pSnapRingMem, 0, nrOfSamples * snapshotMemSize);        // Initialize it to all zeroes

   // Allocate trigger ringbuffer to memorize being triggered
   TBool *triggerRing = new TBool [nrOfSamples];                   // Allocate local memory
   memset ((void*) triggerRing, 0, nrOfSamples * sizeof (TBool));  // Initialize it to all zeroes

   for (;;) {  // Forever
      // Accept new shapshot from drivers
      copySelectedVars ();  // Take from each driver the data specified for this channel by the configuration file

      // Copy local snapshot buffer to shared memory for real time display
      channelMemBox.request ();                             // Get the semaphore of the channel shared memory
      memcpy (pChannelMem, pSnapshotMem, snapshotMemSize);  // Copy the snapshot to it
      channelMemBox.release ();                             // Release the semaphore of the channel shared memory

      // Prepare to copy new sample to ring buffer
      currentIndex = next (currentIndex);  // Make currentIndex point to the cyclically next sample of the ringbuffer
      oldestIndex = next (currentIndex);   // The sample that will be overwritten next is the oldest sample

      // Copy local snapshot buffer to current sample of ring buffer
      memcpy (
         (void*) ((char*) pSnapRingMem + currentIndex * snapshotMemSize),  // Compute right place in ring buffer
         pSnapshotMem,
         snapshotMemSize
      );

      // Find out which sample is the oldest unwritten sample
      // Unwritten means: not yet written to disk due to triggering

      if (oldestUnwrittenIndex == currentIndex)  // Every snapshot was unwritten before reading the new snapshot
         oldestUnwrittenIndex = oldestIndex;     // Every snapshot is still unwritten after reading the new snapshot

      if (oldestUnwrittenIndex == -1)            // No snapshot was unwritten before reading the new snapshot
         oldestUnwrittenIndex = currentIndex;    // Only the new snapshot is yet unwritten to disk

      // Memorize wether or not the current sample will trigger recording
      if (initialized)                               // Initialisation already took place
         triggerRing [currentIndex] = triggered ();  // Record wether or not the current sample will trigger disk recording
      else {                                         // Initialisation not yet took place
         triggerRing [currentIndex] = false;         // Do not yet trigger
         initialized = true;                         // Memorize having initialized
      }
      /*
      Remark:
      Triggering should be blocked in the first cycle because e.g. CHANGE triggers would be activated by the change from zero data
      to non zero data, that will take place at channel startup.
      */

      shift ();  // Memorize current snapshot data before obtaining new data to triggering on data change possible

      // If recording was triggered and enough post samples were gathered
      // dump to disk the unwritten part of the ring buffer
      if    (triggerRing [
               (oldestIndex + nrOfPreSamples) % nrOfSamples  // Compute index of trigger sample
            ]) {
         dumpRingToDisk (                                    // Write in-memory ringbuffer current place of circular disk file
            pSnapRingMem,                                    // Pointer to ringbuffer
            snapshotMemSize,                                 // Size of one indivisable snapshot within the ring buffer
            nrOfSamples,                                     // Number of snapshots within ringbuffer
            oldestUnwrittenIndex,                            // Oldest snapshot that was not yet written to disk before
            currentIndex                                     // Index of current snapshot within ringbuffer
         );
         oldestUnwrittenIndex = -1;                          // Everything written to disk, that is: nothing unwritten
      }

      DosSleep (sleepTime);  // Leave time for low priority threads to operate
   }
   delete [] triggerRing;    // Deallocate local memory before program termination
}
