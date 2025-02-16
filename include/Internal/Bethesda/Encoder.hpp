#pragma once

namespace Internal::Encoder
{
	std::optional<std::wstring> FromUTF8ToUTF16(std::string_view a_value) noexcept;
	std::optional<std::string> FromUTF16ToUTF8(std::wstring_view a_value) noexcept;
}
