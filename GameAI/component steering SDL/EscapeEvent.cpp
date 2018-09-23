#include "EscapeEvent.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment1
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/
EscapeEvent::EscapeEvent(bool myBool)
	:Event(ESCAPE_EVENT)
{
	mBool = myBool;
}

EscapeEvent::~EscapeEvent()
{

}

bool EscapeEvent::getBool() const
{
	return mBool;
}
