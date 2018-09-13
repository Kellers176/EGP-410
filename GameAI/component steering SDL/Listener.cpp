#include "Listener.h"


Listener::Listener(EventSystem* pEventSystem, EventType type)
	:EventListener()
{
	pEventSystem->addListener(type, this);
}

Listener::~Listener()
{

}

void Listener::handleEvent(const Event& theEvent)
{

}