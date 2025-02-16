#include "Internal/Structs/Colors.hpp"

namespace Internal::Colors
{
	static constexpr auto RED_KEY = "Red"sv;
	static constexpr auto GREEN_KEY = "Green"sv;
	static constexpr auto BLUE_KEY = "Blue"sv;
	static constexpr auto ALPHA_KEY = "Alpha"sv;

	Color MakeColor(
		std::uint8_t a_red, std::uint8_t a_green, std::uint8_t a_blue, std::uint8_t a_alpha) noexcept
	{
		auto color = Color();
		SetColor(color, a_red, a_green, a_blue, a_alpha);
		return color;
	}

	std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t> GetColor(const Color& a_rgba) noexcept
	{
		return std::make_tuple(
			GetRed(a_rgba),
			GetGreen(a_rgba),
			GetBlue(a_rgba),
			GetAlpha(a_rgba));
	}

	bool SetColor(Color& a_rgba, std::uint8_t a_red, std::uint8_t a_green, std::uint8_t a_blue, std::uint8_t a_alpha) noexcept
	{
		return SetRed(a_rgba, a_red) &&
			   SetGreen(a_rgba, a_green) &&
			   SetBlue(a_rgba, a_blue) &&
			   SetAlpha(a_rgba, a_alpha);
	}

	std::uint8_t GetRed(const Color& a_rgb) noexcept
	{
		return a_rgb.find<std::uint8_t>(RED_KEY).value_or(0);
	}

	bool SetRed(Color& a_rgb, std::uint8_t a_red) noexcept
	{
		return a_rgb.insert(RED_KEY, a_red);
	}

	std::uint8_t GetGreen(const Color& a_rgb) noexcept
	{
		return a_rgb.find<std::uint8_t>(GREEN_KEY).value_or(0);
	}

	bool SetGreen(Color& a_rgb, std::uint8_t a_green) noexcept
	{
		return a_rgb.insert(GREEN_KEY, a_green);
	}

	std::uint8_t GetBlue(const Color& a_rgb) noexcept
	{
		return a_rgb.find<std::uint8_t>(BLUE_KEY).value_or(0);
	}

	bool SetBlue(Color& a_rgb, std::uint8_t a_blue) noexcept
	{
		return a_rgb.insert(BLUE_KEY, a_blue);
	}

	std::uint8_t GetAlpha(const Color& a_rgba) noexcept
	{
		return a_rgba.find<std::uint8_t>(ALPHA_KEY).value_or(0);
	}

	bool SetAlpha(Color& a_rgba, std::uint8_t a_alpha) noexcept
	{
		return a_rgba.insert(ALPHA_KEY, a_alpha);
	}
}
