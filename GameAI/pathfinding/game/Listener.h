#pragma once
#include "EventListener.h"
#include "EventSystem.h"
#include "Event.h"

class Listener :public EventListener
{
public:
	Listener(EventSystem*, EventType);
	~Listener();

	void handleEvent(const Event&);

private:

};