// ======================== BEGIN OF GENERATED CODE ========================



// ====== BEGIN OF License COMMENT BLOCK, INCLUDE IN ANY COPY OF THIS GENERATED CODE AND DO NOT REMOVE ======
//
// I M P O R T A N T   S A F E T Y   N O T I C E
//
// THIS CODE IS INTENDED SOLELY FOR EDUCATIONAL PURPOSES AND IS FUNDAMENTALLY UNSUITABLE FOR CONTROLLING REAL SYSTEMS.
// IT IS STRICKTLY PROHIBITED TO USE THIS GENERATED CODE IN ANY SITUATION THAT ENTAILS RISK OF DAMAGE OR INJURIES.
//
// USE OF THIS CODE IS GOVERNED BY THE QQUICK LICENSE (WWW.QQUICK.ORG/LICENSE).
// YOUR LICENSE TO USE THIS GENERATED CODE AUTOMATICALLY ENDS IF YOU REMOVE OR LEAVE OUT THIS LICENSE COMMENT BLOCK OR THE CODE THAT GENERATED IT. 
//
// ====== END OF License COMMENT BLOCK, INCLUDE IN COPY OF THIS GENERATED CODE AND DO NOT REMOVE ======



// Generator: SimPyLC 3.9.4
// Generated: 2021-02-22 12:40:22.041774
// Target platform: Arduino



// ____________ General includes ____________

#include <math.h>



// ____________ Arduino macros ____________

#define getNowExact() micros ()
#define getNowInexact() millis ()



// ____________ General macros ____________

// Circuit operations

#define mark4(marker, trueValue, condition, falseValue) marker = (condition) ? (trueValue) : (falseValue)
#define mark3(marker, trueValue, condition) if (condition) marker = (trueValue)
#define mark2(marker, trueValue) marker = (trueValue)
#define mark1(marker) marker = True

#define trigger2(oneshot, condition) oneshot.value = oneshot.memo; oneshot.memo = (condition); oneshot.value = !oneshot.value and oneshot.memo
#define trigger1(oneshot) oneshot.value = !oneshot.memo; oneshot.memo = True
#define spiked1(oneshot) (oneshot.value)

#define latch2(latch, condition) if (condition) latch = True
#define latch1 (latch) latch = True

#define unlatch2(latch, condition) if (condition) latch = False
#define unlatch1 (latch) latch = False

#define set4(register, trueValue, condition, falseValue) register = (condition) ? (trueValue) : (falseValue)
#define set3(register, trueValue, condition) if (condition) register = (trueValue)
#define set2(register, trueValue) register = (trueValue)
#define set1(register) register = 1

#define reset2(timer, condition) if (condition) {timer.exact = nowExact; timer.inexact = nowInexact;}
#define reset1(timer) timer.exact = nowExact; timer.inexact = nowInexact
#define elapsed1(timer) ((nowInexact - timer.inexact) < 3.6e6 ? 1e-6 * (nowExact - timer.exact) : 1e-3 * (nowInexact - timer.inexact))

// Support operations

#define update()\
    thenExact = nowExact; nowExact = getNowExact(); period = 1e-6 * (nowExact - thenExact);\
    nowInexact = getNowInexact();\
    first = False;

// Types

#define False 0
#define True 1
#define Bool bool
#define UInt unsigned long
#define Int long
#define Float double
#define Marker int
#define Oneshot struct {int value; int memo;}
#define Latch int
#define Register double
#define Timer struct {unsigned long exact; unsigned long inexact;}

// Math operations

#define abs1(value) fabs (value)
#define max2(value0, value1) fmax (value0, value1)
#define min2(value0, value1) fmin (value0, value1)
#define limit3(value, aLimit0, aLimit1) min (max (value, aLimit0), aLimit1)  
#define limit2(value, aLimit) limit3 (value, -aLimit, aLimit)
#define digit2(value, index) getDigit (int (value), index)

// ____________ General functions ____________

int getDigit (int value, int index) {
    return (index == 0) ? value % 10 : getDigit (value / 10, --index);
}

// ____________ General variables ____________

UInt nowExact = 0;
UInt thenExact = 0;
UInt nowInexact = 0;
Float period = 1;
Bool first = True;



// ____________ PLC variables ____________

// ______ Module: pidController ______

// Page: p i d controller

// Group: inputs

Register uRefIn = 0;
Register uActIn = 0;

// Group: outputs

Register uOut = 0;

// Group: p i d settings

Register cProp = 0;
Register cInt = 1;
Register cDif = 0;

// Group: raw correction terms

Register uCorIn = 0;
Register uCorIntIn = 0;
Register uCorDifIn = 0;

// Group: scaled correction terms

Register uCorOut = 0;
Register uCorIntOut = 0;
Register uCorDifOut = 0;

// Group: auxiliary

Register uMax = 3.5;
Register nMax = 1024;
Register uCorOldIn = 0;
Register nActIn = 0;
Register nOut = 0;

// Group: physics

Marker simulatePhysics = False;
Register transferFactor = 1;



// ____________ PLC cycle ____________

void cycle () {

	// ______ Module: pidController ______

	// ___ Sweep ___
	set2 (uRefIn, (uMax / 2));
	set3 (nActIn, (transferFactor * nOut), simulatePhysics);
	set2 (uActIn, ((nActIn * uMax) / nMax));
	set2 (uCorOldIn, uCorIn);
	set2 (uCorIn, (uRefIn - uActIn));
	set2 (uCorIntIn, limit2 ((uCorIntIn + (uCorIn * period)), uMax));
	set2 (uCorDifIn, ((uCorIn - uCorOldIn) / period));
	set2 (uCorOut, (cProp * uCorIn));
	set2 (uCorIntOut, (cInt * uCorIntIn));
	set2 (uCorDifOut, (cDif * uCorDifIn));
	set2 (uOut, ((uCorOut + uCorIntOut) + uCorDifOut));
	set2 (nOut, ((uOut * nMax) / uMax));

    // ______ System ______

    update ();
}



// ======================== END OF GENERATED CODE ========================

/*
Copyright (C) 2013 - 2020 GEATEC engineering

This program is free software.
You can use, redistribute and/or modify it, but only under the terms stated in the QQuickLicence.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY, without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the QQuickLicence for details.

The QQuickLicense can be accessed at: http://www.qquick.org/license.html

__________________________________________________________________________


 THIS PROGRAM IS FUNDAMENTALLY UNSUITABLE FOR CONTROLLING REAL SYSTEMS !!

__________________________________________________________________________

It is meant for training purposes only.

Removing this header ends your licence.
*/

int const analogInPin = A3;
int const analogOutPin = 2;

void setup () {
    // pinMode (analogInPin, INPUT);
    pinMode (analogOutPin, OUTPUT);
    Serial.begin(9600);
}

void loop () {
    nActIn = analogRead (analogInPin);
    cycle ();
    analogWrite  (analogOutPin, nOut);
    Serial.println (nActIn);  
}       

