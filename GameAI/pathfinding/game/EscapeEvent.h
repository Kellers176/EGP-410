#pragma once
#include "Event.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment1
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

class EscapeEvent : public Event
{
public:
	EscapeEvent(bool myBool);
	~EscapeEvent();

	bool getBool() const;



private:
	bool mBool;


};