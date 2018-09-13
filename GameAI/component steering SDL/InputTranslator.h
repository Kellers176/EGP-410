#pragma once
/*Author: Kelly Herstine
Class: EGP-310
<Section 01>
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/
#include "Listener.h"



class InputTranslator : public EventListener
{
public:
	//calls the events
	InputTranslator();
	~InputTranslator();

	void initInputTranslator();
	void cleanupInputTranslator();

	void handleEvent(const Event &theEvent);

	void updateInputTranslator(double dt);


private:
};