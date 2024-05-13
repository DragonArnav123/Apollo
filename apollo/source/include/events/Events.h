#pragma once

#include "../core/Core.h"

namespace Apollo {
namespace Events {

	class APOLLO_API IEvent
	{
	public:
		using Type = APccstr;

	public:
		IEvent() = default;
		virtual ~IEvent() = default;

		virtual Type GetType() const = 0;
	};

	class APOLLO_API EventDispatcher
	{
	public:
		using Handle = APsize;
		using CallbackFn = std::function<void (const IEvent &)>;

		static constexpr Handle NO_HANDLE = -1;

	public:
		EventDispatcher() = delete;
		virtual ~EventDispatcher() = default;

		static bool Initialize();
		static void Terminate();

		static Handle AddDispatcher(IEvent::Type type, const CallbackFn &callBack); 
		static Handle AppendDispatcher(IEvent::Type type, const CallbackFn &callBack, Handle prevHandle); 
		static Handle PrependDispatcher(IEvent::Type type, const CallbackFn &callback, Handle nextHandle);
		static void RemoveDispatcher(IEvent::Type type, Handle handle);
		static std::optional<const CallbackFn *> RetrieveDispatcher(IEvent::Type type, Handle handle);
		static std::optional<CallbackFn *> AlterDispatcher(IEvent::Type type, Handle handle);

		static APsize NumberOfRegisteredEvents();
		static APsize NumberOfCallbacksForEvent(IEvent::Type type);

		static void PostEvent(const IEvent &event);

	private:
		static std::map<
			IEvent::Type,
			std::vector<CallbackFn>> *s_Callbacks;
	};

}
}