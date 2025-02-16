#include "Internal/Bethesda/Encoder.hpp"

_STL_DISABLE_DEPRECATED_WARNING
#include <codecvt>

namespace Internal::Encoder
{
	std::optional<std::wstring> FromUTF8ToUTF16(std::string_view a_value) noexcept
	{
		try {
			auto converter = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>();
			return converter.from_bytes(a_value.data(), a_value.data() + a_value.size());
		}
		catch (const std::exception&) {
			return std::nullopt;
		}
	}

	std::optional<std::string> FromUTF16ToUTF8(std::wstring_view a_value) noexcept
	{
		try {
			auto converter = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>();
			return converter.to_bytes(a_value.data(), a_value.data() + a_value.size());
		}
		catch (const std::exception&) {
			return std::nullopt;
		}
	}
}

_STL_RESTORE_DEPRECATED_WARNING
