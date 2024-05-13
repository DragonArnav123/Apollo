#include "../include/APpch.h"
#include "../include/utils/Error.h"
#include "../include/core/Log.h"

namespace Apollo {
namespace Util {

	Error::Error(const std::string &type, const std::string &message, bool isFatal)
		:
		m_Type(type),
		m_Message(message),
		m_IsFatal(isFatal)
	{
	}

	Error::~Error()
	{
	}

	void Error::LogToConsole() const
	{
		if (m_IsFatal)
		{
			AP_CORE_CRITICAL("{0}: {1}", m_Type, m_Message);
		} else
		{
			AP_CORE_WARN("{0}: {1}", m_Type, m_Message);
		}
	}

}
}