#pragma once
/*Author: Kelly Herstine
Class: EGP-310
<Section 01>
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/
#include "Event.h"
#include "Vector2D.h"


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