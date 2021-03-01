// ******************** Defines

#define usePlc

// ******************** Includes

#include <windows.h>
#include <ioStream.h>
#include <stdIo.h>
#include "stackLib.h"

// ******************** Constants

const int sleepTime_ms = 1000;

// ******************** Variables

bool quit = false;

// ******************** Global functions

DWORD WINAPI doBlockingConsoleIO (LPVOID threadParam) {
	char key;

	for (;;) {
		cout << endl << "Command (q = quit all application parts): ";
		cin >> key;

		switch (key) {
			case 'q':
				quit = true;
				break;
		}

		Sleep (sleepTime_ms);
	}

	return 0;
}
// ******************** Main function

void main () {
	CreateThread (0, 0, doBlockingConsoleIO, 0, 0, 0);
	createState ();
	requestState ();
	clearJobQueue ();	// Clear queue before initializing stack image
							// so prediction will go right during initialisation
	initializeStackImages ();
	sm.continueProcessing = true;	// Signals initialisation done.
											// Persistence driver may start now without the
											// risk of saving an uninitialized stackimage
											// the first time the program is run.
	releaseState ();

	while (sm.continueProcessing && !quit) {
		queryMoveRequest ();
		Sleep (sleepTime_ms);
	}

	sm.continueProcessing = false;
	closeState ();
}