#include "../include/APpch.h"
#include "../include/core/Timestep.h"

namespace Apollo {

	Timestep::Timestep(APf32 deltaTime)
		: m_DeltaTime(deltaTime)
	{
	}

	APf32 Timestep::GetDeltaTime() const
	{
		return m_DeltaTime;
	}

	Timestep::operator float()
	{
		return m_DeltaTime;
	}

	Timestep::operator double()
	{
		return (APf64) m_DeltaTime;
	}

}