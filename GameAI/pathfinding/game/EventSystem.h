#pragma once

#include <map>
#include <Trackable.h>

class Event;
#pragma once

#include <map>
#include <Trackable.h>

class Event;
class EventListener;
enum EventType;

using namespace std;

class EventSystem :public Trackable
{
public:
	static EventSystem* getInstance();
	static void initInstance();
	static void cleanupInstance();

	void fireEvent(const Event& theEvent);
	void addListener(EventType type, EventListener* pListener);
	void removeListener(EventType type, EventListener* pListener);
	void removeListenerFromAllEvents(EventListener* pListener);

private:
	EventSystem();
	~EventSystem();
	static EventSystem* mpEventSystem;
	multimap< EventType, EventListener* > mListenerMap;

	void dispatchAllEvents(const Event& theEvent);

};
