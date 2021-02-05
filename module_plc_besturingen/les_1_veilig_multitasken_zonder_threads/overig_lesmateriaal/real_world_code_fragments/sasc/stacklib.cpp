// ******************** Defines

#define stateMemName "sharedMem_logist_state"
#define stateSemName "mutexSem_logist_state"
#define greenPlc
#define defPlc

// ******************** Includes

#include <stdlib.h>
#include <time.h>
#include "layout.h"
#include "stackLib.h"

// ******************** Variable definitions

//	====== State memory management

TStateMap stateMap;
TStateMem *pStateMem;
TStateSem stateSem;
int stateSemCount;

// ******************** Function definitions

// ====== Stack image management

// --- Initialisation and corrections

void initializeStackImages () {
	TStateGuard stateGuard;

	int locationIndex = 0;
	TLocatorParts locatorParts;

	// Unknown location

	{
		TLocation &loc = as.locations [locationIndex++];

		loc.idealCoordinates.x = 0;
		loc.idealCoordinates.y = 0;
		loc.idealCoordinates.z = 0;

		locatorParts.chTypePart = char (ltUnknown);
		locatorParts.iXPart = 0;
		locatorParts.chYPart = ' ';
		locatorParts.iZPart = 0;
		locatorFromParts (loc.locator, locatorParts);
	}

	// Import location

	{
		TLocation &loc = as.locations [locationIndex++];

		loc.idealCoordinates.x = 0;
		loc.idealCoordinates.y = 0;
		loc.idealCoordinates.z = 0;

		locatorParts.chTypePart = char (ltImport);
		locatorParts.iXPart = 0;
		locatorParts.chYPart = ' ';
		locatorParts.iZPart = 0;
		locatorFromParts (loc.locator, locatorParts);
	}

	// Export location

	{
		TLocation &loc = as.locations [locationIndex++];

		loc.idealCoordinates.x = 0;
		loc.idealCoordinates.y = 0;
		loc.idealCoordinates.z = 0;

		locatorParts.chTypePart = char (ltExport);
		locatorParts.iXPart = 0;
		locatorParts.chYPart = ' ';
		locatorParts.iZPart = 0;
		locatorFromParts (loc.locator, locatorParts);
	}

	// Spreader location

	{
		TLocation &loc = as.locations [locationIndex++];

		loc.idealCoordinates.x = 0;
		loc.idealCoordinates.y = 0;
		loc.idealCoordinates.z = 0;

		locatorParts.chTypePart = char (ltSpreader);
		locatorParts.iXPart = 0;
		locatorParts.chYPart = ' ';
		locatorParts.iZPart = 0;
		locatorFromParts (loc.locator, locatorParts);
	}

   // Bulk tilting

	{
		TLocation &loc = as.locations [locationIndex++];

		loc.idealCoordinates.x = cXBulk;
		loc.idealCoordinates.y = cYBulk;
		loc.idealCoordinates.z = cZBulk;

		locatorParts.chTypePart = char (ltBulk);
		locatorParts.iXPart = 0;
		locatorParts.chYPart = ' ';
		locatorParts.iZPart = 0;
		locatorFromParts (loc.locator, locatorParts);
	}

   // Normal tiltings

	{for (int tiltNr = 1; tiltNr <= 6; tiltNr++) {
		TLocation &loc = as.locations [locationIndex++];

		switch (tiltNr) {
			case 1:
				loc.idealCoordinates.x = cXTilt1;
				break;
			case 2:
				loc.idealCoordinates.x = cXTilt2;
				break;
			case 3:
				loc.idealCoordinates.x = cXTilt3;
				break;
			case 4:
				loc.idealCoordinates.x = cXTilt4;
				break;
			case 5:
				loc.idealCoordinates.x = cXTilt5;
				break;
			case 6:
				loc.idealCoordinates.x = cXTilt6;
				break;
		}
		loc.idealCoordinates.y = cYTilt;
		loc.idealCoordinates.z = cZTilt;

		locatorParts.chTypePart = char (ltTilt);
		locatorParts.iXPart = tiltNr;
		locatorParts.chYPart = ' ';
		locatorParts.iZPart = 0;
		locatorFromParts (loc.locator, locatorParts);
	}}

	// Other locations

   {for (int xNr = 1; xNr <= cXCels; xNr++) {

      // RTS locations, used for transfer or storage

      if (xNr > cXNrBeforeRts && xNr < cXNrAfterRts) {

			// Transfer

			TLocation &loc = as.locations [locationIndex++];

			loc.idealCoordinates.x = cXMinStack + cDXCel * (xNr - 1); 
			loc.idealCoordinates.y = cYRts;
			loc.idealCoordinates.z = cZRts;

			locatorParts.chTypePart = char (ltRts);
			locatorParts.iXPart = xNr;
			locatorParts.chYPart = ' ';
			locatorParts.iZPart = 0;
			locatorFromParts (loc.locator, locatorParts);

			// Storage

			{for (int zNr = 1; zNr <= cZCels; zNr++) {
				TLocation &loc = as.locations [locationIndex++];

				loc.idealCoordinates.x = cXMinStack + cDXCel * (xNr - 1);
				loc.idealCoordinates.y = cYRts;
				loc.idealCoordinates.z = cZMaxStack - cDZCont * zNr;
				
				locatorParts.chTypePart = char (ltRts);
				locatorParts.iXPart = xNr;
				locatorParts.chYPart = 'E';
				locatorParts.iZPart = zNr;
				locatorFromParts (loc.locator, locatorParts);
			}}
		}

      // Normal stack locations

      {for (int yNr = 1; yNr <= cYCels; yNr++) {
         if (! (  (yNr == 1 && xNr > cXNrBeforeTilts && xNr < cXNrAfterTilts)
                  ||
                  (yNr == cYCels && xNr < cXNrAfterRts)
               )
         ) {
				for (int zNr = 1; zNr <= cZCels; zNr++) {
					TLocation &loc = as.locations [locationIndex++];

					loc.idealCoordinates.x = cXMinStack + cDXCel * (xNr - 1);
					switch (yNr) {
						case 1:
							loc.idealCoordinates.y = cYStackA;
							break;
						case 2:
							loc.idealCoordinates.y = cYStackB;
							break;
						case 3:
							loc.idealCoordinates.y = cYStackC;
							break;
						case 4:
							loc.idealCoordinates.y = cYStackD;
							break;
						case 5:
							loc.idealCoordinates.y = cYStackE;
							break;
					}
					loc.idealCoordinates.z = cZMaxStack - cDZCont * zNr;
					
					locatorParts.chTypePart = char (ltStack);
					locatorParts.iXPart = xNr;
					locatorParts.chYPart = 'A' + yNr - 1;
					locatorParts.iZPart = zNr;
					locatorFromParts (loc.locator, locatorParts);
				}
			}
      }}
	}}

	// Version has start value 0, must be distinct from initialisation value -1
	// used for local stack image in persistence driver

	predictStackImage ();	// Just copy fixed part.
									// Varying part is copied after loading persistent image.
}

void correctStackImage (TLocator completeLocator, bool put, bool predicted) {
	/*
	This function only looks to the occupation status of locations other than, but related to,
	the location denoted by completelocator where the get or put is going to take place.
	The occupation status of the source- or destination location itself is checked by adminGet and adminPut.
	So no checks are found in correctStackImage for B and T1 - T7.
	RTS transfer locations are never checked for their occupation status as their contents are volatile.
	*/

	TStateGuard stateGuard;

	TStackImage &stackImage = predicted ? ps : as;
	stackImage.version++;

	TLocatorParts knownParts;
	partsFromLocator (knownParts, completeLocator);

	if (knownParts.chTypePart == char (ltStack) || knownParts.chTypePart == char (ltRts)) {
		{for (int locationIndex = 0; locationIndex < maxNrOfLocations; locationIndex++) {
			TLocation &checkedLoc = stackImage.locations [locationIndex];
			TLocatorParts checkedParts;
			partsFromLocator (checkedParts, checkedLoc.locator);

			if (checkedParts.iXPart == knownParts.iXPart) {				// If known and checked location on same row
				if (knownParts.chTypePart == char (ltRts)) {				//		If known location is RTS location 
					if (knownParts.chYPart == ' ') {							//			If known RTS location used for transfer
						if (															//				If
							checkedParts.chTypePart == char (ltRts) &&	//				checked location is RTS location
							checkedParts.chYPart != ' ' &&					//				used for storage
							checkedLoc.containerId								//				and administered as occupied
						) {
							checkedLoc.containerId = 0;						//					Erase occupant

							TGeneralErrorText text;
							strcpy (text, put ? "Container neergezet op" : "Container opgepakt van");
							strcat (text, " RTS frame op bezette opslaglocatie, surplus container verwijderd van ");
							strcat (text, checkedLoc.locator);
							strcat (text, predicted ? " van voorspelde stack image" : " van actuele stack image");
							newGeneralError (geStackImage, text);			//					Report error
						}
					}
					else {															//			Else (known RTS location used for storage)
						if (															//				If
							checkedParts.chTypePart == char (ltRts) &&	//				checked location is RTS location
							checkedParts.chYPart == ' ' &&					//				used for transfer
							checkedLoc.containerId								//				and administered as occupied
						) {
							checkedLoc.containerId = 0;						//					Erase occupant
																						//					Container and frame driven away, no error
						}
					}
				}

				if (knownParts.chYPart != ' ') {								//		If known RTS or regular stack location for storage
					if (checkedParts.chYPart == knownParts.chYPart) {	//			If known loc. and checked loc. on same line		
						if (															//				If
							checkedParts.iZPart < knownParts.iZPart &&	//				below known container
							!checkedLoc.containerId								//				but administrated as non-occupied
						) {
							checkedLoc.containerId = getNewUnknownContainerId ();	//		Assume unknown container

							TGeneralErrorText text;
							strcpy (text, put ? "Container neergezet op" : "Container opgepakt van");
							strcat (text, " zwevende locatie, onbekende container geplaatst op ");
							strcat (text, checkedLoc.locator);
							strcat (text, predicted ? " van voorspelde stack image" : " van actuele stack image");
							newGeneralError (geStackImage, text);			//					Report error
						}
						else if (													//				Else if
							checkedParts.iZPart > knownParts.iZPart &&	//				above known, uncovered container
							checkedLoc.containerId								//				but administrated as occupied
						) {
							checkedLoc.containerId = 0;						//					Erase occupant

							TGeneralErrorText text;
							strcpy (text, put ? "Container neergezet op" : "Container opgepakt van");
							strcat (text, " begraven locatie, bedekkende container verwijderd van ");
							strcat (text, checkedLoc.locator);
							strcat (text, predicted ? " van voorspelde stack image" : " van actuele stack image");
							newGeneralError (geStackImage, text);			//					Report error
						}
					}
				}
			}	
		}}
	}
}

// --- Displacements

void adminGet (TLocator completeSourceLocator, TContainerId containerId, bool predicted) {
   /*
   Function adminGet is called from the following functions:
   -  notifyGet (normal move)
      Parameter containerId is derived from the tag.
      If this fails it's taken from the actual stack image.
      If this fails because the pickup location is unknown or unoccupied, a negative id is generated.
      So containerId is non-zero coming from notifyGet, unless the tagtable is faulty.
      Physical reality dictates that a container was there, otherways it couldn't have been picked up.
      So the model (stack image) is adjusted by always coming up with a non-zero id
   -  queryMoveRequest (virtual move)
      Parameter containerId is taken from the actual stack image, including the unknown location
      If the location is empty, containerId is left 0.
   -  predictStackImage (prediction)
      Parameter containerId is taken from the predicted stackImage.
      If the location is empty, containerId is left 0.
   In the following cases a 0 containerId is replaced by a generated one in adminGet:
   -  Pickup from import location, that is what the import location is for: generating containers
   -  Pickup from an RTS frame, an occupied frame may have been put into place without notice
   */

   TStateGuard stateGuard;

	TStackImage &stackImage = predicted ? ps : as;
	stackImage.version++;

	TLocatorParts sourceParts;
	partsFromLocator (sourceParts, completeSourceLocator);

   TLocator spreaderLocator;
	TLocatorParts spreaderParts = {char (ltSpreader), 0, ' ', 0};
	locatorFromParts (spreaderLocator, spreaderParts);

   TLocation
      &sourceLoc = stackImage.locations [getLocationIndex (completeSourceLocator)],
      &spreaderLoc = stackImage.locations [getLocationIndex (spreaderLocator)];

   if (sourceParts.chTypePart == char (ltUnknown)) {									// If picked up from unknown location
		TGeneralErrorText text;
		strcpy (text, "Container opgepakt van onbekende positie uit ");
		strcat (text, predicted ? "voorspelde" : "actuele");
		strcat (text, " stack image");
		newGeneralError (geStackImage, text);												//		Report pickup from unknown location
                                                                              //    also if virtual pickup from ltUnknown
      spreaderLoc.containerId = containerId;                                  //    Always prefer containerId from caller,
   }                                                                          //    stems from image, tag or generation
   else if (sourceParts.chTypePart == char (ltImport)) {                      // Else if picked up from import location
      spreaderLoc.containerId = getNewUnknownContainerId ();                  //    Create new, unknown container
   }
   else if (																						//		Else if picked up from RTS frame
         sourceParts.chTypePart == char (ltRts) && sourceParts.chYPart == ' '
		) {
         if (containerId == 0) {                                              //       If parameter 0 passed from image
            spreaderLoc.containerId = getNewUnknownContainerId ();            //          Assume one has arrived
         }
         else  {                                                              //       Else
            spreaderLoc.containerId = containerId;                            //          Accept param. from image or tag
         }
   }
   else {                                                                     //	Else (storage location or tilting)
   	if (sourceLoc.containerId) {														   //		If a container there in stack image
         if (                                                                 //			If
            (sourceLoc.containerId > 0)												   //       it has a known id in image
            &&                                                                //       and
				(containerId != sourceLoc.containerId)                            //			the tag inferred id deviates
         ) {
				TSContainerId
					sExpectedContainerId,
					sActualContainerId;
   			_itoa (containerId, sExpectedContainerId, 10);
				_itoa (sourceLoc.containerId, sActualContainerId, 10);

				TGeneralErrorText text;
				strcpy (text, "Container ");
				strcat (text, sActualContainerId);
				strcat (text, " opgepakt in plaats van verwachte container ");
				strcat (text, sExpectedContainerId);
				strcat (text, " op locatie ");
				strcat (text, completeSourceLocator);
				strcat (text, " van ");
				strcat (text, predicted ? "voorspelde" : "actuele");
				strcat (text, " stack image, image gecorrigeerd");
				newGeneralError (geStackImage, text);								      //				Report id mismatch
			}
		}
		else {																					   //		Else (no container there in image)
			TGeneralErrorText text;
			strcpy (text, "Container opgepakt van als leegstaand bekende locatie ");
			strcat (text, completeSourceLocator);
			strcat (text, " van ");
			strcat (text, predicted ? "voorspelde" : "actuele");
			strcat (text, " stack image, opgepakte container toegevoegd aan image");
			newGeneralError (geStackImage, text);										   //			Report pickup from empty location
      }

      spreaderLoc.containerId = containerId;                                  //    Always prefer container id from caller
	}

   sourceLoc.containerId = 0;																   //	Register source location now empty
	correctStackImage (completeSourceLocator, false, predicted);				   //	Correct related locations

   TLocator dupplicateLocator;
	strcpy (dupplicateLocator, spreaderLocator);
	for (;;) {
		findNextDupplicateContainerId (dupplicateLocator, spreaderLocator, predicted);

		if (!strcmp (dupplicateLocator, spreaderLocator))
			break;

		TContainerId dupplicateContainerId;
		containerIdFromLocator (dupplicateContainerId, dupplicateLocator, predicted);

      if (!dupplicateContainerId) {  // If adminGet in uninitialized predicted stackImage (results from hand-editing)
         break;                      //    Avoid jamming error buffer by an avalanche of reports
      }

		TSContainerId	sDupplicateContainerId;
		_itoa (dupplicateContainerId, sDupplicateContainerId, 10);

		TGeneralErrorText text;
		strcpy (text, "Container met dezelfde identifier, ");
		strcat (text, sDupplicateContainerId);
		strcat (text, ", geregistreerd op locatie ");
		strcat (text, dupplicateLocator);
		strcat (text, " van ");
		strcat (text, predicted ? "voorspelde" : "actuele");
		strcat (text, " stack image");
		newGeneralError (geStackImage, text);
	}

	if (!predicted) {
		predictStackImage ();
	}
}

void adminPut (TLocator completeTargetLocator, bool predicted) {
	TStateGuard stateGuard;

	TStackImage &stackImage = predicted ? ps : as;
	stackImage.version++;

	TLocatorParts targetParts;
	partsFromLocator (targetParts, completeTargetLocator);

   TLocator spreaderLocator;
	TLocatorParts spreaderParts = {char (ltSpreader), 0, ' ', 0};
	locatorFromParts (spreaderLocator, spreaderParts);

	TLocation
      &targetLoc = stackImage.locations [getLocationIndex (completeTargetLocator)],
      &spreaderLoc = stackImage.locations [getLocationIndex (spreaderLocator)];

   if (targetParts.chTypePart == char (ltUnknown)) {                          // If put down at unknown location
		TGeneralErrorText text;
		strcpy (text, "Container neergezet op onbekende positie in ");
		strcat (text, predicted ? "voorspelde" : "actuele");
		strcat (text, " stack image");
		newGeneralError (geStackImage, text);												//		Report putdown at unknown location

      targetLoc.containerId = spreaderLoc.containerId;                        //    Store at the unknown location in image
   }
   else if (targetParts.chTypePart == char (ltExport)) {                      // Else if put down at export location
      ;                                                                       //    Let container vanish by not storing it
                                                                              //    (so do nothing)
   }
   else if (																						// Else if put down on RTS frame
		targetParts.chTypePart == char (ltRts) && targetParts.chYPart == ' '
	) {
      targetLoc.containerId = getNewUnknownContainerId ();                    //    Force it to unknown as it may be   
	}                                                                          //    driven away or swapped
   else {                                                                     //  Else (storage location or tilting)
	   if (targetLoc.containerId) {														   //		If location occupied in stack image
			TGeneralErrorText text;
			strcpy (text, "Container neergezet op reeds bezette locatie ");
			strcat (text, completeTargetLocator);
			strcat (text, " van ");
			strcat (text, predicted ? "voorspelde" : "actuele");
			strcat (text, " stack image, bezettende container verwijderd uit image");
			newGeneralError (geStackImage, text);										   //		   Report putdown at occupied loc.
      }

      targetLoc.containerId = spreaderLoc.containerId;                        //    Store in image
	}

	spreaderLoc.containerId = 0;                                               //	Register spreader now empty
   correctStackImage (completeTargetLocator, true, predicted);					   //	Correct related locations

	if (!predicted) {
		predictStackImage ();
	}

	// ...
	// Should actual coordinates be considered of use in future versions,
	// this is the place to program storing them.
	// They should't be used for location recognition without any restrictions,
	// as this will make the stack "drift away".
	// Also it will interfere with the possibility to work with an only partially known stack image.
}


void predictStackImage () {
	TStateGuard stateGuard;

	TVersion oldPsVersion = ps.version;
	ps = as;						        // Fast blockcopy instead of for-loop, matters here, often called!
	ps.version = oldPsVersion + 1;  // Price to be paid for efficiency (copying complete image instead of locations only)

	TLocatorParts locatorParts;
	TContainerId containerId;

	// Pending job

	partsFromLocator (locatorParts, jq.jobs [0] .fromLocator);
	containerIdFromLocator (containerId, jq.jobs [0] .fromLocator, true);

	if (locatorParts.chTypePart != char (ltNone)) {		               // If there's pending job
   	TLocator spreaderLocator;
	   TLocatorParts spreaderParts = {char (ltSpreader), 0, ' ', 0};
	   locatorFromParts (spreaderLocator, spreaderParts);
      TContainerId spreaderContainerId;
      containerIdFromLocator (spreaderContainerId, spreaderLocator);

     if (!spreaderContainerId) {                                     //	   If container not yet picked up
                                                                     //    -  Don't use sm.twistLocked,
                                                                     //    it's not set in virtual displacements
																		               //    - In case it was put down already,
                                                                     //    it wouldn't be pending!
			adminGet (jq.jobs [0] .fromLocator, containerId, true);     //       Predict picking it up
		}
		adminPut (jq.jobs [0] .toLocator, true);			               //    Predict putting it down
	}

	// Other jobs

	{for (int jobQueueIndex = 1; jobQueueIndex < maxNrOfJobsInQueue; jobQueueIndex++) {
		partsFromLocator (locatorParts, jq.jobs [jobQueueIndex] .fromLocator);
		containerIdFromLocator (containerId, jq.jobs [jobQueueIndex] .fromLocator, true);

		if (locatorParts.chTypePart != char (ltNone)) {
			adminGet (jq.jobs [jobQueueIndex] .fromLocator, containerId, true);
			adminPut (jq.jobs [jobQueueIndex] .toLocator, true);
		}
	}}
}

// --- Searching the stack image

void partsFromLocator (TLocatorParts &parts, TLocator locator) {
	int pos = 1;

	parts.chTypePart = locator [0];
   parts.iXPart = 0,
   parts.chYPart = ' ',
   parts.iZPart = 0;

   while (isdigit (locator [pos])) {
      parts.iXPart += locator [pos] - '0';
      parts.iXPart *= 10;
      pos++;
   }
   parts.iXPart /= 10;

   if (isalpha (locator [pos])) {
      parts.chYPart = locator [pos];
      pos++;
   }

   if (isdigit (locator [pos]))
      parts.iZPart = locator [pos] - '0';
}

void locatorFromParts (TLocator &locator, TLocatorParts parts){
	int pos = 0;

	locator [pos++] = parts.chTypePart;
	locator [pos] = '\0';

	if (parts.iXPart) {
		_itoa (parts.iXPart, locator + pos, 10);
		pos = strlen (locator);
	}

	if (parts.chYPart != ' ') {
		locator [pos++] = parts.chYPart;
		locator [pos] = '\0';
	}

	if (parts.iZPart) {
		_itoa (parts.iZPart, locator + pos, 10);
		pos = strlen (locator);
	}
}

void upperLocatorFromPartialLocator (TLocator &upperLocator, TLocator partialLocator, bool occupied, bool predicted) {
	TStateGuard stateGuard;

	TStackImage &stackImage = predicted ? ps : as;

	TLocatorParts upperParts;
	partsFromLocator (upperParts, partialLocator);

   switch (upperParts.chTypePart) {                      // Deal with import, export and unknown location
      case char (ltImport):
      case char (ltExport):
      case char (ltUnknown):
         upperParts.iXPart = 0;
         upperParts.chYPart = ' ';
         upperParts.iZPart = 0;
         locatorFromParts (upperLocator, upperParts);
         return;                                         // That's all, so return quickly
   }

	upperParts.iZPart = -2;											// Mark no matching occpied or free location found yet

	{for (int locationIndex = 0; locationIndex < maxNrOfLocations; locationIndex++) {
																			// For all locations
		TLocation &candidateLoc = stackImage.locations [locationIndex];
		TLocatorParts candidateParts;
		partsFromLocator (candidateParts, candidateLoc.locator);

		if (																//		If location matches
			candidateParts.chTypePart == upperParts.chTypePart &&
			candidateParts.iXPart == upperParts.iXPart &&
			candidateParts.chYPart == upperParts.chYPart
		) {
			if (upperParts.iZPart == -2) {						//			If it's the first one matching
				upperParts.iZPart = -1;								//				Mark matching location found, not yet proven occupied
			}
			if (candidateLoc.containerId) {						//			If it's occupied
				if (candidateParts.iZPart > upperParts.iZPart) {	//		If it's higher than any old match
					upperParts.iZPart = candidateParts.iZPart;		//			Remember it's height (and that a matching occupied
				}															//					location was found)
			}
		}
	}}

	if (																	// If searching for RTS frame, occupied or not
		upperParts.chTypePart == char (ltRts)
		&&
		upperParts.chYPart == ' '
	) {
		if (upperParts.iZPart == -2) {							//		If no matching RTS frame location found, occupied or not
			upperParts.chTypePart = char (ltUnknown);			//			Conclude unknown
			upperParts.iXPart = 0;
			upperParts.chYPart = ' ';
			upperParts.iZPart = 0;
		}
		else {															//		If matching RTS frame location found, occupied or not
			upperParts.iZPart = 0;									//			Clear eventual -1 (unoccupied) from z coordinate
		}
	}
	else if (occupied) {												// If searching for occupied but no RTS frame
		if (upperParts.iZPart <= -1) {							//		If no matching occupied location found
			upperParts.chTypePart = char (ltUnknown);			//			Conclude unknown
			upperParts.iXPart = 0;
			upperParts.chYPart = ' ';
			upperParts.iZPart = 0;
		}
	}
	else {																// If searching for non-occupied but no RTS frame
		if (upperParts.iZPart == -2) {							//		If no matching occupied or free location found
			upperParts.chTypePart = char (ltUnknown);			//			Conclude unknown
			upperParts.iXPart = 0;
			upperParts.chYPart = ' ';
			upperParts.iZPart = 0;
		}
		else {															//		If matching occupied or free location found
			if (															//			If it's a location where containers can be stacked on
				upperParts.chTypePart == char (ltStack)		//			top of each other
				|| 
				(upperParts.chTypePart == char (ltRts) && upperParts.chYPart != ' ')
			) {
				// When expanding partial locators, RTS locations with non-blank chYPart are treated as normal stacking space,
				// Only the crane driver can detect the presence of a frame and wether it's a full frame or an empty frame.
				// Any frame, full or empty, is considered potentially empty stacking space as it may be gone without notice.
				// Color may be adapted to denote "frame or empty space".
				if	(upperParts.iZPart >= cZCels) {				//				If maximum stacking height reached
					upperParts.chTypePart = char (ltUnknown);	//					Conclude unknown
					upperParts.iXPart = 0;
					upperParts.chYPart = ' ';
					upperParts.iZPart = 0;
				}
				else {													//				If maximum stacking height not yet reached
					if (upperParts.iZPart == -1) {				//					If spot found but still emptpy
						upperParts.iZPart = 1;						//						Conclude space on the ground
					}
					else {												//					If spot not empty
						upperParts.iZPart++;							//						Conclude space on top of container
					}
				}
			}
			else if (													//				If bulk- or normal tilting
				upperParts.chTypePart == char (ltBulk)
				||
				upperParts.chTypePart == char (ltTilt)
			) {
				if (upperParts.iZPart > -1) {						//					If there's a container already there
					upperParts.chTypePart = char (ltUnknown);	//						Conclude unknown
					upperParts.iXPart = 0;
					upperParts.chYPart = ' ';
					upperParts.iZPart = 0;
				}
				else {													//					If there's no container already there
					upperParts.iZPart = 0;							//						Conclude it's free for use
				}
			}
		}
	}
	locatorFromParts (upperLocator, upperParts);
}

void findNextDupplicateContainerId (TLocator &dupplicateLocator, TLocator referenceLocator, bool predicted) {
	TStateGuard stateGuard;	

	TStackImage &stackImage = predicted ? ps : as;

	int referenceIndex = getLocationIndex (referenceLocator);
	int dupplicateIndex = getLocationIndex (dupplicateLocator);

	do {
		dupplicateIndex = dupplicateIndex++ % maxNrOfLocations;
	} while (stackImage.locations [dupplicateIndex] .containerId != stackImage.locations [referenceIndex] .containerId);

	strcpy (dupplicateLocator, stackImage.locations [dupplicateIndex] .locator);
}

void locatorFromContainerId (TLocator &locator, TContainerId containerId, bool predicted) {
	TStateGuard stateGuard;
	
	TStackImage &stackImage = predicted ? ps : as;

	TLocatorParts unknownParts = {char (ltUnknown), 0, ' ', 0};
	locatorFromParts (locator, unknownParts);
	{for (int locationIndex = 0; locationIndex < maxNrOfLocations; locationIndex++) {
		TLocation &loc = stackImage.locations [locationIndex];
		if (loc.containerId == containerId) {
			strcpy (locator, loc.locator);
			return;
		}
	}}
}

void containerIdFromLocator (TContainerId &containerId, TLocator locator, bool predicted) {
	TStateGuard stateGuard;

	TStackImage &stackImage = predicted ? ps : as;

	containerId = 0;
	{for (int locationIndex = 0; locationIndex < maxNrOfLocations; locationIndex++) {
		TLocation &loc = stackImage.locations [locationIndex];
		if (!strcmp (loc.locator, locator)) {
			containerId = loc.containerId;
			return;
		}
	}}
}

void locatorFromCoordinates (
	TLocator &locator, 
	TCoordinates coordinates, 
	bool useActualCoords,
	bool predicted
) {
	TStateGuard stateGuard;

	TStackImage &stackImage = predicted ? ps : as;

	TLocatorParts locatorParts = {char (ltUnknown), 0, ' ', 0};
	locatorFromParts (locator, locatorParts);

	{for (int locationIndex = 0; locationIndex < maxNrOfLocations; locationIndex++) {
		TLocation &loc = stackImage.locations [locationIndex];
		TCoordinates &locCoordinates = useActualCoords ? loc.actualCoordinates : loc.idealCoordinates;

		TLocatorParts locatorParts;
		partsFromLocator (locatorParts, loc.locator);

		if (
			abs (locCoordinates.x - coordinates.x) < cXRecognitionMargin &&
			abs (locCoordinates.y - coordinates.y) < cYRecognitionMargin
		) {
		   if (
			   (locatorParts.iZPart == 0 && abs (locCoordinates.z - coordinates.z) < cZRecognitionMargin1)
				// Bulk tilting, normal tiltings and RTS frames have iZPart == 0 but carry at most one container, 
				// so recognition margin cZRecognitionMargin1 is appropriate here
				||
			   (locatorParts.iZPart == 1 && abs (locCoordinates.z - coordinates.z) < cZRecognitionMargin1)
				// Stack or RTS non-frame storage layer 1
				||
			   (locatorParts.iZPart == 2 && abs (locCoordinates.z - coordinates.z) < cZRecognitionMargin2)
				// Stack or RTS non-frame storage layer 2
				||
			   (locatorParts.iZPart == 3 && abs (locCoordinates.z - coordinates.z) < cZRecognitionMargin3)
				// Stack or RTS non-frame storage layer 3
				||
			   (locatorParts.iZPart == 4 && abs (locCoordinates.z - coordinates.z) < cZRecognitionMargin4)
				// Stack or RTS non-frame storage layer 4
			) {
				strcpy (locator, loc.locator);
				return;
			}
		}
	}}
}

void coordinatesFromLocator (
	TCoordinates &coordinates, 
	TLocator locator, 
	bool useActualCoords, 
	bool predicted
) {
	TStateGuard stateGuard;

	TStackImage &stackImage = predicted ? ps : as;

	TLocation &loc = stackImage.locations [getLocationIndex (locator)];
	coordinates = useActualCoords ? loc.actualCoordinates : loc.idealCoordinates;
}

void partialLocatorFromCoordinates (
	TLocator &partialLocator, 
	TCoordinates partialCoordinates,
	bool rtsAsStorage,
	bool useActualCoords,
	bool predicted
) {
	TStateGuard stateGuard;

	TStackImage &stackImage = predicted ? ps : as;

	TLocatorParts locatorParts = {char (ltUnknown), 0, ' ', 0};
	locatorFromParts (partialLocator, locatorParts);

	{for (int locationIndex = 0; locationIndex < maxNrOfLocations; locationIndex++) {
		TLocation &loc = stackImage.locations [locationIndex];
		TCoordinates &locCoordinates = useActualCoords ? loc.actualCoordinates : loc.idealCoordinates;
		if (
			abs (locCoordinates.x - partialCoordinates.x) < cXRecognitionMargin &&
			abs (locCoordinates.y - partialCoordinates.y) < cYRecognitionMargin
		) {
			partsFromLocator (locatorParts, loc.locator);
			if (locatorParts.chTypePart == char (ltRts)) {
				locatorParts.chYPart = rtsAsStorage ? 'E' : ' ';
			}
			locatorParts.iZPart = 0;
			locatorFromParts (partialLocator, locatorParts);
			return;
		}
	}}
}

void partialCoordinatesFromLocator (
	TCoordinates &partialCoordinates,
	TLocator partialLocator,
	bool useActualCoords,
	bool predicted
) {
	TStateGuard stateGuard;

	TStackImage &stackImage = predicted ? ps : as;

	TLocator locator;
	upperLocatorFromPartialLocator (locator, partialLocator, false, predicted);		// Attempt unoccupied expansion
	TLocatorParts locatorParts;
	partsFromLocator (locatorParts, locator);
	if (locatorParts.chTypePart == char (ltUnknown)) {											// If unoccupied expansion failed
		upperLocatorFromPartialLocator (locator, partialLocator, true, predicted);		//		Attempt occupied expansion
	}

	TLocation &loc = stackImage.locations [getLocationIndex (locator)];
	partialCoordinates = useActualCoords ? loc.actualCoordinates : loc.idealCoordinates;
	partialCoordinates.z = 0;
}

int getLocationIndex (TLocator completeLocator) {
	TStateGuard stateGuard;

	{for (int locationIndex = 0; locationIndex < maxNrOfLocations; locationIndex++) {
		if (!strcmp (as.locations [locationIndex] .locator, completeLocator)) {
			return locationIndex;
		}
	}}
	return -1;
}

// ====== Tag table management

void tagFromContainerId (TTag &tag, TContainerId containerId) {
	TStateGuard stateGuard;

	strcpy (tag, "");
	{for (int tagTableIndex = 0; tagTableIndex < maxNrOfTags; tagTableIndex++) {
		TTagRecord &tagRec = tt.tagRecords [tagTableIndex];
	   if (tagRec.containerId == containerId) {
			strcpy (tag, tagRec.tag);
			return;
		}
	}}	
}

void containerIdFromTag (TContainerId &containerId, TTag tag) {
	TStateGuard stateGuard;

	containerId = 0;
	{for (int tagTableIndex = 0; tagTableIndex < maxNrOfTags; tagTableIndex++) {
		TTagRecord &tagRec = tt.tagRecords [tagTableIndex];
	   if (!strcmp (tagRec.tag, tag)) {
			containerId = tagRec.containerId;
			return;
		}
	}}
	
	// Only here if tag not found

	tt.version++;

	{for (int tagTableIndex = 0; tagTableIndex < maxNrOfTags; tagTableIndex++) {
		TTagRecord &tagRec = tt.tagRecords [tagTableIndex];
	   if (!strcmp (tagRec.tag, "")) {
			strcpy (tagRec.tag, tag);
			containerId = getNewUnknownContainerId ();
			tagRec.containerId = containerId;
			return;
		}
	}}
}

void changeContainerIdOfTag (TTag tag, TContainerId newContainerId) {
	TStateGuard stateGuard;

	tt.version++;

	{for (int tagTableIndex = 0; tagTableIndex < maxNrOfTags; tagTableIndex++) {
		TTagRecord &tagRec = tt.tagRecords [tagTableIndex];
		if (!strcmp (tagRec.tag, tag)) {
			tagRec.containerId = newContainerId;
		}
	}}	
}

// ====== ContainerId management

int getNewUnknownContainerId () {
	TStateGuard stateGuard;

	{for (int attemptCount = 0;;attemptCount++) {
		int proposedContainerId = -1 * rand ();
		bool found = false;
		{for (int locationIndex = 0; !found && locationIndex < maxNrOfLocations; locationIndex++) {
			found = as.locations [locationIndex] .containerId == proposedContainerId;
		}}
		{for (int tagTableIndex = 0; !found && tagTableIndex < maxNrOfTags; tagTableIndex++) {
			found = tt.tagRecords [tagTableIndex] .containerId == proposedContainerId;
		}}
		if (!found) {
			return proposedContainerId;
		}
		else if (attemptCount > maxReasonableNumberOfAttemptsToGenerateUniqueNegativeContainerId) {
			newGeneralError (
				geStackImage, 
				"Generatie van unieke negatieve identifier voor onbekende container verloopt moeizaam"
			);
			// Do not return yet, sooner or later an unused id should be found, statistically..
		}
	}}
}

// ====== Job queue management

void eraseJob (TJob &job) {	// Doesn't need stateGuard, as it only touches state memory in commision
	TLocatorParts locatorParts = {char (ltNone), 0, ' ', 0};
	TLocator locator;
	locatorFromParts (locator, locatorParts);
	strcpy (job.fromLocator, locator);
	strcpy (job.toLocator, locator);
	job.isVirtual = false;
}

void insertJobAtIndex (TJob job, int index) {
	TStateGuard stateGuard;

	jq.version++;

	if (index < 0 || index >= maxNrOfJobsInQueue) {
		index = maxNrOfJobsInQueue - 1;
	}

	{for (; index > 1; index--) {							// Insertion at index 1 and 0 without further conditions
		TLocatorParts fromParts;
		partsFromLocator (fromParts, jq.jobs [index - 1] .fromLocator);
		if (fromParts.chTypePart != char (ltNone)) {	// Insertion at nonzero index: jq.jobs [index - 1] must be occupied
			break;
		}
	}}

	{for (int jobQueueIndex = maxNrOfJobsInQueue - 1; jobQueueIndex > index; jobQueueIndex--) {	// Make place
		jq.jobs [jobQueueIndex] = jq.jobs [jobQueueIndex - 1];
	}}

	jq.jobs [index] = job;																								// Insert

	predictStackImage ();
}

void deleteJobFromIndex (int index) {
	TStateGuard stateGuard;

	jq.version++;

	if (index < 0 || index >= maxNrOfJobsInQueue) {
		index = maxNrOfJobsInQueue - 1;
	}

	{for (; index > 0; index--) {							// Deletion at index 0 without further conditions
		TLocatorParts fromParts;
		partsFromLocator (fromParts, jq.jobs [index] .fromLocator);
		if (fromParts.chTypePart != char (ltNone)) {	// Deletion at nonzero index: jq.jobs [index] must be occupied
			break;
		}
	}}

	{for (int jobQueueIndex = index; jobQueueIndex < maxNrOfJobsInQueue - 1; jobQueueIndex++) {	// Advance
		jq.jobs [jobQueueIndex] = jq.jobs [jobQueueIndex + 1];
	}}

	eraseJob (jq.jobs [maxNrOfJobsInQueue - 1]);																	// Add empty at tail

	predictStackImage ();
}

bool advanceJobQueue () {
	TStateGuard stateGuard;

	jq.version++;

	{for (int jobQueueIndex = 1; jobQueueIndex < maxNrOfJobsInQueue; jobQueueIndex++) {	// Overwrite pending
		jq.jobs [jobQueueIndex - 1] = jq.jobs [jobQueueIndex];
	}}
	
	eraseJob (jq.jobs [maxNrOfJobsInQueue - 1]);														// Add empty at tail

	predictStackImage ();

	TLocatorParts fromParts;
	partsFromLocator (fromParts, jq.jobs [0] .fromLocator);
	if (fromParts.chTypePart != char (ltNone)) {
		return false;
	}
	else {
		return true;
	}
}

void clearJobQueue (bool includePending) {
	TStateGuard stateGuard;

	jq.version++;

	{for (int jobQueueIndex = includePending ? 0 : 1; jobQueueIndex < maxNrOfJobsInQueue; jobQueueIndex++) {
		eraseJob (jq.jobs [jobQueueIndex]);
	}}

	predictStackImage ();
}

// ====== Request management

void scheduleMoveRequest (TLocator partialFromLoc, TLocator partialToLoc, int jobQueueIndex, bool isVirtual) {
	TStateGuard stateGuard;

	jq.version++;

	TJob job;
	upperLocatorFromPartialLocator (job.fromLocator, partialFromLoc, true, true);
	upperLocatorFromPartialLocator (job.toLocator, partialToLoc, false, true);
	job.isVirtual = isVirtual;
	insertJobAtIndex (job, jobQueueIndex);
}

void requestResetSequenceControl () {
	TStateGuard stateGuard;
	
	clearJobQueue ();			// Prevent overwriting reset request with next job and the use of an obsolete job queue.
									// Also erase pending job, it has already been transmitted to the sequence control but
									// is destroyed by the reset
									// Reset should be used only in exceptional situations.

	rq.version++;
	rq.softPlcRequestCode = plc.rqReset;
}

void requestResumeSequenceControl () {
	TStateGuard stateGuard;

	clearJobQueue (false);	// Prevent overwriting resume request with next job and the use of an obsolete job queue.
									// Don't erase pending job, it has already been transmitted to the sequence control and
									// is needed for stack prediction.
									// Resume should be used only in exceptional situations.

	rq.version++;
	rq.softPlcRequestCode = plc.rqResume;
}

// ====== Sequence control transfer functions

// --- Passing requests to sequence control

void queryMoveRequest () {
	TStateGuard stateGuard;
	
	TLocatorParts
		fromParts0,
		fromParts1;

	partsFromLocator (fromParts0, jq.jobs [0].fromLocator);
	partsFromLocator (fromParts1, jq.jobs [1].fromLocator);

	if (fromParts1.chTypePart != char (ltNone) && fromParts0.chTypePart == char (ltNone)) {
		jq.version++;
		advanceJobQueue ();
		TJob &job = jq.jobs [0];
		if (job.isVirtual) {
			TContainerId containerId;
			containerIdFromLocator (containerId, job.fromLocator);
			adminGet (job.fromLocator, containerId);  // Also used to transfer container from the unknown locator
         TLocator toLocator;
         strcpy (toLocator, job.toLocator);
         jq.version++;
			eraseJob (job);                           // Erase now, so prediction adminPut doesn't think it's pending
			adminPut (toLocator);
			as.version++;	                           // Redundant, but safe
		}
		else {
			rq.version++;
			coordinatesFromLocator (rq.fromCoordinates, job.fromLocator);
			coordinatesFromLocator (rq.toCoordinates, job.toLocator);
			rq.softPlcRequestCode = plc.rqGetPut;
			// Don't erase pending job
		}
	}
}

// --- Notifying twistlock status changes

void notifyGet (TCoordinates coordinates, TTag tag) {
	TStateGuard stateGuard;

	TLocator locator;
	locatorFromCoordinates (locator, coordinates);

	TContainerId containerId = 0;

	if (strcmp (tag, "")) {
		containerIdFromTag (containerId, tag);
	}
	else {
		newGeneralError (geStackImage, "Tag onleesbaar");

		TLocation loc = as.locations [getLocationIndex (locator)];
		TLocatorParts locatorParts;
		partsFromLocator (locatorParts, locator);

		if (locatorParts.chTypePart == char (ltUnknown)) {
			containerId = getNewUnknownContainerId ();  // Don't use containerIdFromLocator, it will retrieve a containerId
      }                                              // that's in use and stored at locator with type ltUnknown in image
		else {
			if (loc.containerId) {
				containerId = loc.containerId;
			}
			else {
				containerId = getNewUnknownContainerId ();
			}
		}

		adminGet (locator, containerId);
	}
}

void notifyPut (TCoordinates coordinates) {
	TStateGuard stateGuard;

	TLocator locator;
	locatorFromCoordinates (locator, coordinates);
	
	jq.version++;
	eraseJob (jq.jobs [0]);  // Erase now, so prediction adminPut doesn't think it's pending

	adminPut (locator);
}

// ====== Reporting and error handling

// --- Reporting

void newReport (TReport report) {
	TStateGuard stateGuard;

	{for (int reportIndex = reportListSize - 1; reportIndex >= 1; reportIndex--) {
		rl [reportIndex] = rl [reportIndex - 1];
	}}

	report.version = rl [1] .version + 1;
	rl [0] = report;
}

// --- Error handling

void newError (TError error) {
	TStateGuard stateGuard;
	
	{for (int errorIndex = errorListSize - 1; errorIndex >= 1; errorIndex--) {
		el [errorIndex] = el [errorIndex - 1];
	}}

	error.version = el [1] .version + 1;
	el [0] = error;
}

void newGeneralError (TGeneralErrorCode code, TGeneralErrorText text) {
	TStateGuard stateGuard;

	static const TError emptyError;	// Initalized to all zeroes once

	TError error = emptyError;			// Set to all zeroes each time
	error.generalErrorCode = code;
	strcpy (error.generalErrorText, text);

	newError (error);
}

// ====== Process cooperation primitives

// --- State memory and concurrency management

bool continueProcessing () {
	return sm.continueProcessing;
}

void createState () {
   HANDLE stateMap = CreateFileMapping (
      HANDLE (0xFFFFFFFF),
      NULL,
      PAGE_READWRITE,
      0,
      sizeof (TStateMem),
      stateMemName
   );

   pStateMem = (TStateMem*) MapViewOfFile (
      stateMap,
      FILE_MAP_READ | FILE_MAP_WRITE,
      0,
      0,
      0
   );

   memset (pStateMem, '\0', sizeof (TStateMem));

   stateSem = CreateMutex (NULL, FALSE, stateSemName);

	srand ((unsigned) time (NULL));  // Called once in current process, just what's needed
}

void openState () {
   HANDLE stateMap = OpenFileMapping (
      FILE_MAP_READ | FILE_MAP_WRITE,
      FALSE,
      stateMemName
   );

   pStateMem = (TStateMem*) MapViewOfFile (
      stateMap,
      FILE_MAP_READ | FILE_MAP_WRITE,
      0,
      0,
      0
   );

   stateSem = OpenMutex (MUTEX_ALL_ACCESS, FALSE, stateSemName);

	srand ((unsigned) time (NULL));	// Called once in current process, just what's needed
}

void closeState () {
	CloseHandle (stateSem);
	CloseHandle (stateMap);
}

void hurryLogist () {
   SetPriorityClass (GetCurrentProcess (), REALTIME_PRIORITY_CLASS);
   SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_TIME_CRITICAL);
}


void relaxLogist () {
   SetPriorityClass (GetCurrentProcess (), NORMAL_PRIORITY_CLASS);
   SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_NORMAL);
}

void requestState () {
	if (!stateSemCount++) {		// Don't leave counting to OS, gain maximum control (like e.g. printing the counter)
		WaitForSingleObject (stateSem, INFINITE);
	}
}

void releaseState () {
	if (!--stateSemCount) {		// Don't leave counting to OS, gain maximum control (like e.g. printing the counter)
		ReleaseMutex (stateSem);
	}
}

void hurryAndRequestState () {
	hurryLogist ();
	requestState ();
}

void releaseStateAndRelax () {
	releaseState ();
	relaxLogist ();
}

// --- State versioning

bool versionChanged (TVersion sharedVersion, TVersion &localVersion) {
	TStateGuard stateGuard;

	if (sharedVersion > localVersion) {
		localVersion = sharedVersion;	// Needed! It may be the case that only a part excluding the version is copied from
		return true;						// the shared record to the local record. Also, the local version may be kept in a
	}											// variable separate from the local record used for content-access.
	else {
		return false;
	}
}

// ====== Cooperation with SoftPlc

// --- Communication with SoftPlc

void callInitPlc () {
	initPlc ();
}
