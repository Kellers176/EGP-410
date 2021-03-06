#pragma once
#include "Event.h"
#include "Vector2D.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment1
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

class MousePosition : public Event
{
public:
	MousePosition(int x, int y);
	~MousePosition();

	Vector2D getMousePosition() /*const*/;

private:
	int mPosX;
	int mPosY;


};