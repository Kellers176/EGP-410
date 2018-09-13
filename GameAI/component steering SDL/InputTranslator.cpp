#include "InputTranslator.h"
#include "InputSystem.h"

InputTranslator::InputTranslator()
{
}

InputTranslator::~InputTranslator()
{
}

void InputTranslator::initInputTranslator()
{
	//EventSystem::getInstance()->addListener(ESCAPE_EVENT, this);
}

void InputTranslator::cleanupInputTranslator()
{
}

void InputTranslator::handleEvent(const Event & theEvent)
{
	/*if (theEvent.getType() == ESCAPE_EVENT)
	{
		const EscapeEvent& escapeEvent = static_cast<const EscapeEvent&>(theEvent);
		EventSystem::getInstance()->fireEvent(QuitEvent());
	}*/


}

void InputTranslator::updateInputTranslator(double dt)
{
}
