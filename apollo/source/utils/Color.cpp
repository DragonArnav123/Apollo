#include "../include/utils/Color.h"

static glm::vec4 EnsureNormalized(const glm::vec4 &v)
{
	// soft asserts and clamps
	return v;
}

static Apollo::Util::Color::NRGBA HexToNormalizedRGBA(
	const Apollo::Util::Color::HEX &hex)
{
	// @TODO: put an assert here for size of string
	// "#rrggbbaa"
	auto calculateComp = [](char coeff16, char coeff1) -> APf32 {
		APi32 c = std::atoi(&coeff16) * 16 + std::atoi(&coeff1) * 1;
		return (APf32) (c / 255.0f);
	};

	glm::vec4 color;
	color.r = calculateComp(hex[1], hex[2]);
	color.r = calculateComp(hex[3], hex[4]);
	color.r = calculateComp(hex[5], hex[6]);
	color.r = calculateComp(hex[7], hex[8]);

	return color;
}

static Apollo::Util::Color::NRGBA RGBAToNormalizedRGBA(
	const Apollo::Util::Color::RGBA &rgba)
{
	// put assets here (soft assert)

	return glm::vec4(
		rgba.r / 255.0f,
		rgba.g / 255.0f,
		rgba.b / 255.0f,
		rgba.a / 255.0f);
}

static Apollo::Util::Color::HEX NormalizedRGBAToHex(
	const Apollo::Util::Color::NRGBA &nrgba)
{
	// clamps and asserts

	std::string hex = std::string("#");

	auto calculateComp = [](APf32 comp) -> std::string {
		APi32 _comp = 255.0f * comp;
		static const char *_nums = "0123456789";

		std::string s = std::string("");
		s += _nums[_comp % 10];
		s += _nums[(_comp / 10) % 10];

		return s;
	};

	glm::vec4 c = EnsureNormalized(nrgba);

	hex += calculateComp(c.r);
	hex += calculateComp(c.g);
	hex += calculateComp(c.b);
	hex += calculateComp(c.a);

	return hex;
}

static Apollo::Util::Color::RGBA NormalizedRGBAToRGBA(
	const Apollo::Util::Color::NRGBA &nrgba)
{
	const glm::vec4 c = EnsureNormalized(nrgba);

	return glm::ivec4(
		c.r * 255.0f,
		c.g * 255.0f,
		c.b * 255.0f,
		c.a * 255.0f);
}

namespace Apollo {
namespace Util {

	Color::Color(const HEX &hex)
		:
		m_Color(HexToNormalizedRGBA(hex))
	{
	}

	Color::Color(const RGBA &rgba)
		:
		m_Color(RGBAToNormalizedRGBA(rgba))
	{
	}

	Color::Color(const NRGBA &nrgba)
		:
		m_Color(EnsureNormalized(nrgba))
	{
	}

	Color::~Color()
	{
	}

	Color::HEX Color::GetHex() const
	{
		return NormalizedRGBAToHex(m_Color);
	}

	Color::RGBA Color::GetRGBA() const
	{
		return NormalizedRGBAToRGBA(m_Color);
	}

	const Color::NRGBA &Color::GetNormalizedRGBA() const
	{
		return m_Color;
	}

	void Color::SetHex(const HEX &hex)
	{
		m_Color = HexToNormalizedRGBA(hex);
	}

	void Color::SetRGBA(const RGBA &rgba)
	{
		m_Color = RGBAToNormalizedRGBA(rgba);
	}

	void Color::SetNormalizedRGBA(const NRGBA &nrgba)
	{
		m_Color = EnsureNormalized(nrgba);
	}

}
}