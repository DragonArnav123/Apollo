#include "../include/APpch.h"
#include "../include/events/Events.h"

namespace Apollo {
namespace Events {

	std::map<
		IEvent::Type,
		std::vector<EventDispatcher::CallbackFn>> *EventDispatcher::s_Callbacks = nullptr;

	bool EventDispatcher::Initialize()
	{
		s_Callbacks = 
			new std::map<
				IEvent::Type,
				std::vector<EventDispatcher::CallbackFn>>();

		return (s_Callbacks != nullptr);
	}

	void EventDispatcher::Terminate()
	{
		delete s_Callbacks;
	}

	EventDispatcher::Handle EventDispatcher::AddDispatcher(
		IEvent::Type type, 
		const EventDispatcher::CallbackFn &callBack)
	{
		Handle handle = 0;

		// Add the event
		// Since we want to add an event, use the [] operator
		s_Callbacks->operator[](type).push_back(callBack);
		handle = s_Callbacks->at(type).size() - 1;

		return handle;
	}

	EventDispatcher::Handle EventDispatcher::AppendDispatcher(
		IEvent::Type type, 
		const EventDispatcher::CallbackFn &callBack, 
		EventDispatcher::Handle prevHandle)
	{
		// Check if the event type exists
		if (s_Callbacks->find(type) == s_Callbacks->end())
		{
			// Event does not exist
			return EventDispatcher::NO_HANDLE;
		}

		// Get the vector
		std::vector<CallbackFn> &v = s_Callbacks->at(type);

		// Insert the element
		v.insert(v.begin() + prevHandle + 1, callBack);

		return prevHandle + 1;
	}

	EventDispatcher::Handle EventDispatcher::PrependDispatcher(
		IEvent::Type type,
		const EventDispatcher::CallbackFn &callBack,
		EventDispatcher::Handle nextHandle)
	{
		// Check if the event type exists
		if (s_Callbacks->find(type) == s_Callbacks->end())
		{
			// Event does not exist
			return EventDispatcher::NO_HANDLE;
		}

		// Get the vector
		std::vector<CallbackFn> &v = s_Callbacks->at(type);

		// Insert the element
		v.insert(v.begin() + nextHandle, callBack);

		return nextHandle; 
	}

	void EventDispatcher::RemoveDispatcher(
		IEvent::Type type,
		EventDispatcher::Handle handle)
	{
		// Check if the type exists
		if (s_Callbacks->find(type) == s_Callbacks->end())
		{
			// Type does not exist
			return;
		}

		std::vector<CallbackFn> &v = s_Callbacks->at(type);

		// Remove the callback
		v.erase(v.begin() + handle);
	}

	std::optional<const EventDispatcher::CallbackFn *> EventDispatcher::RetrieveDispatcher(
		IEvent::Type type,
		EventDispatcher::Handle handle)
	{
		// Check if type and handle exist
		if (s_Callbacks->find(type) == s_Callbacks->end())
		{
			// Type not found
			return std::nullopt;
		}
		else
		{
			// Check if handle is valid
			if (handle >= s_Callbacks->at(type).size())
			{
				return std::nullopt;
			}
			return std::optional<const CallbackFn *>(&s_Callbacks->at(type)[handle]);
		}
	}

	std::optional<EventDispatcher::CallbackFn *> EventDispatcher::AlterDispatcher(
		IEvent::Type type,
		EventDispatcher::Handle handle)
	{
		// Check if type and handle exist
		if (s_Callbacks->find(type) == s_Callbacks->end())
		{
			// Type not found
			return std::nullopt;
		}
		else
		{
			// Check if handle is valid
			if (handle >= s_Callbacks->at(type).size())
			{
				return std::nullopt;
			}

			return std::optional<CallbackFn *>(&s_Callbacks->at(type)[handle]);
		}
	}

	APsize EventDispatcher::NumberOfRegisteredEvents()
	{
		return s_Callbacks->size();
	}

	APsize EventDispatcher::NumberOfCallbacksForEvent(IEvent::Type type)
	{
		// Check if type exists
		if (s_Callbacks->find(type) == s_Callbacks->end())
			return 0u;
		return s_Callbacks->at(type).size();
	}

	void EventDispatcher::PostEvent(const IEvent &event)
	{
		// Check if event exist
		if (s_Callbacks->find(event.GetType()) == s_Callbacks->end())
		{
			// Event does not exist
			return;
		}

		// Event exists, iterate through callbacks and call them
		const std::vector<CallbackFn> &Callbacks = s_Callbacks->at(event.GetType());

		for (const auto &callback : Callbacks)
		{
			callback(event);
		}
	}

}
}