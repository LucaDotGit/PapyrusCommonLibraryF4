#pragma once

#include "Internal/Bethesda/Converter.hpp"

namespace System::Single
{
	static constexpr auto SCRIPT_NAME = "System:Single"sv;

	static std::int32_t Decimals(std::monostate)
	{
		return std::numeric_limits<float>::digits10;
	}

	static std::int32_t MaxDecimals(std::monostate)
	{
		return std::numeric_limits<float>::max_digits10;
	}

	static float Min(std::monostate)
	{
		return std::numeric_limits<float>::min();
	}

	static float Max(std::monostate)
	{
		return std::numeric_limits<float>::max();
	}

	static float Epsilon(std::monostate)
	{
		return std::numeric_limits<float>::denorm_min();
	}

	static float NaN(std::monostate)
	{
		return std::numeric_limits<float>::quiet_NaN();
	}

	static float PositiveInfinity(std::monostate)
	{
		return std::numeric_limits<float>::infinity();
	}

	static float NegativeInfinity(std::monostate)
	{
		return -std::numeric_limits<float>::infinity();
	}

	static bool IsNaN(std::monostate,
		float a_float)
	{
		return std::isnan(a_float);
	}

	static bool IsInfinity(std::monostate,
		float a_float)
	{
		return std::isinf(a_float);
	}

	static bool IsPositiveInfinity(std::monostate,
		float a_float)
	{
		return std::isinf(a_float) && a_float > 0.0f;
	}

	static bool IsNegativeInfinity(std::monostate,
		float a_float)
	{
		return std::isinf(a_float) && a_float < 0.0f;
	}

	static float TryParse(std::monostate,
		std::string_view a_string,
		float a_default)
	{
		return ::Internal::Converter::ToFloat(a_string).value_or(a_default);
	}

	static std::string ToString(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		float a_float,
		std::string_view a_format)
	{
		if (a_format.empty()) {
			return ::Internal::Converter::ToString(a_float);
		}

		try {
			return fmt::format(fmt::runtime(a_format), a_float);
		}
		catch (const fmt::format_error& a_error) {
			a_vm.PostError(a_error.what(), a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return {};
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Decimals);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, MaxDecimals);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Min);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Max);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Epsilon);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, NaN);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, PositiveInfinity);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, NegativeInfinity);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNaN);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsInfinity);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsPositiveInfinity);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNegativeInfinity);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, TryParse);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ToString);

		return true;
	}
}
