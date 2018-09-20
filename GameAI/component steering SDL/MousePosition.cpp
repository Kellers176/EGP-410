#include "MousePosition.h"

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
