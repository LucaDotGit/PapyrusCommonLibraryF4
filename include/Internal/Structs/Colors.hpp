#pragma once

namespace Internal::Colors
{
	using Color = RE::BSScript::structure_wrapper<"System:Colors", "Color">;

	[[nodiscard]] Color MakeColor(
		std::uint8_t a_red = 0, std::uint8_t a_green = 0, std::uint8_t a_blue = 0, std::uint8_t a_alpha = 0) noexcept;

	[[nodiscard]] std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t> GetColor(const Color& a_rgba) noexcept;
	bool SetColor(Color& a_rgba, std::uint8_t a_red, std::uint8_t a_green, std::uint8_t a_blue, std::uint8_t a_alpha) noexcept;

	[[nodiscard]] std::uint8_t GetRed(const Color& a_rgb) noexcept;
	bool SetRed(Color& a_rgb, std::uint8_t a_red) noexcept;

	[[nodiscard]] std::uint8_t GetGreen(const Color& a_rgb) noexcept;
	bool SetGreen(Color& a_rgb, std::uint8_t a_green) noexcept;

	[[nodiscard]] std::uint8_t GetBlue(const Color& a_rgb) noexcept;
	bool SetBlue(Color& a_rgb, std::uint8_t a_blue) noexcept;

	[[nodiscard]] std::uint8_t GetAlpha(const Color& a_rgba) noexcept;
	bool SetAlpha(Color& a_rgba, std::uint8_t a_alpha) noexcept;
}
