#pragma once

#include "../core/core.h"

namespace Apollo {

	class APOLLO_API Timestep
	{
	public:
		Timestep(APf32 deltaTime);
		virtual ~Timestep() = default;

		APf32 GetDeltaTime() const;

		operator float();

		operator double();

	private:
		APf32 m_DeltaTime;
	};

}