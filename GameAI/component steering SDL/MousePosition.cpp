#include "MousePosition.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment1
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

MousePosition::MousePosition(int x, int y)
	:Event(MOUSE_POSITION_EVENT)
{
	mPosX = x;
	mPosY = y;
}

MousePosition::~MousePosition()
{
}

Vector2D MousePosition::getMousePosition()
{
	return Vector2D(mPosX, mPosY);
}
