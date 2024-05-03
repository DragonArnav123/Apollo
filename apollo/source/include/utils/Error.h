#pragma once

#include "../APpch.h"
#include "../core/Core.h"

namespace Apollo {
namespace Util {

	class APOLLO_API Error
	{	
	public:
		Error(const std::string &type, const std::string &message);
		virtual ~Error();

		inline const std::string &GetType() const { return m_Type; }
		inline const std::string &GetMessage() const { return m_Message; }

		void Print() const;

	private:
		std::string m_Type;
		std::string m_Message;
	};

}
}