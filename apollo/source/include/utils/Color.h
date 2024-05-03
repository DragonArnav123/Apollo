#pragma once

#include "../APpch.h"
#include "../core/Core.h"
#include "../_glm.h"

namespace Apollo {
namespace Util {

	class APOLLO_API Color 
	{
	public:
		using HEX = std::string;
		using RGBA = glm::ivec4;
		using NRGBA = glm::vec4;

	public:
		Color(const HEX &hex);
		Color(const RGBA &rgba);
		Color(const NRGBA &nrgba);

		virtual ~Color();

		HEX GetHex() const;
		RGBA GetRGBA() const;
		const NRGBA &GetNormalizedRGBA() const;

		void SetHex(const HEX &hex);
		void SetRGBA(const RGBA &rgba);
		void SetNormalizedRGBA(const NRGBA &nrgba);

	private:
		NRGBA m_Color;
	};

}
}