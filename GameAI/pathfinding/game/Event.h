#pragma once

#include <string>
#include <trackable.h>

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	ESCAPE_EVENT,
	MOUSE_POSITION_EVENT,
	F_EVENT,
	D_EVENT,
	A_EVENT,
	NUM_EVENT_TYPES,
};

const string EVENT_NAMES[NUM_EVENT_TYPES] = {
};

class Event :public Trackable
{
public:
	Event();
	Event(EventType type);
	virtual ~Event();

	EventType getType() const { return mType; };
	const string& getEventName() const;

private:
	EventType mType;

};