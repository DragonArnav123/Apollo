#pragma once

#include "../core/Core.h"

namespace Apollo {
namespace Util {

	class APOLLO_API Error
	{	
	public:
		Error(const std::string &type, const std::string &message, bool isFatal);
		virtual ~Error();

		inline const std::string &GetType() const { return m_Type; }
		inline const std::string &GetMessage() const { return m_Message; }

		void LogToConsole() const;

		inline static Util::Error NoError(const std::string &type)
		{
			return Util::Error(type, "No Error", false);
		}

	private:
		std::string m_Type;
		std::string m_Message;
		bool m_IsFatal;
	};

}
}