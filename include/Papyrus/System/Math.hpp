#pragma once

namespace System::Math
{
	static constexpr auto SCRIPT_NAME = "System:Math"sv;

	static double Pi(std::monostate)
	{
		return std::numbers::pi_v<double>;
	}

	static double E(std::monostate)
	{
		return std::numbers::e_v<double>;
	}

	static double Tau(std::monostate)
	{
		return std::numbers::pi_v<double> * 2;
	}

	static std::uint32_t RandomSeed(std::monostate)
	{
		return std::random_device()();
	}

	static bool SeededBool(std::monostate,
		std::uint32_t a_seed)
	{
		auto engine = std::default_random_engine(a_seed);
		auto distributor = std::bernoulli_distribution();
		return distributor(engine);
	}

	static std::int32_t SeededInt(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		std::int32_t a_minInclusive,
		std::int32_t a_maxInclusive,
		std::uint32_t a_seed)
	{
		if (a_minInclusive > a_maxInclusive) {
			a_vm.PostError(::Internal::Errors::MINIMUM_GREATER_THAN_MAXIMUM, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return 0;
		}

		auto engine = std::default_random_engine(a_seed);
		auto distributor = std::uniform_int_distribution(a_minInclusive, a_maxInclusive);
		return distributor(engine);
	}

	static double SeededFloat(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		double a_minInclusive,
		double a_maxExclusive,
		std::uint32_t a_seed)
	{
		if (a_minInclusive > a_maxExclusive) {
			a_vm.PostError(::Internal::Errors::MINIMUM_GREATER_THAN_MAXIMUM, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return 0;
		}

		auto engine = std::default_random_engine(a_seed);
		auto distributor = std::uniform_real_distribution(a_minInclusive, a_maxExclusive);
		return distributor(engine);
	}

	static std::vector<const RE::BSScript::Variable*> SeededShuffle(std::monostate,
		std::vector<const RE::BSScript::Variable*> a_array,
		std::uint32_t a_seed)
	{
		if (a_array.empty()) {
			return {};
		}

		auto engine = std::default_random_engine(a_seed);
		auto array = ::Internal::Copier::CopyArray(a_array);

		std::ranges::shuffle(array, engine);
		return array;
	}

	static std::int32_t Abs(std::monostate,
		std::int32_t a_value)
	{
		return std::abs(a_value);
	}

	static double AbsF(std::monostate,
		double a_value)
	{
		return std::abs(a_value);
	}

	static std::int32_t Min(std::monostate,
		std::int32_t a_left,
		std::int32_t a_right)
	{
		return std::min(a_left, a_right);
	}

	static double MinF(std::monostate,
		double a_left,
		double a_right)
	{
		return std::min(a_left, a_right);
	}

	static std::int32_t Max(std::monostate,
		std::int32_t a_left,
		std::int32_t a_right)
	{
		return std::max(a_left, a_right);
	}

	static double MaxF(std::monostate,
		double a_left,
		double a_right)
	{
		return std::max(a_left, a_right);
	}

	static std::int32_t Clamp(std::monostate,
		std::int32_t a_value,
		std::int32_t a_min,
		std::int32_t a_max)
	{
		return std::clamp(a_value, a_min, a_max);
	}

	static double ClampF(std::monostate,
		double a_value,
		double a_min,
		double a_max)
	{
		return std::clamp(a_value, a_min, a_max);
	}

	static std::int32_t Sign(std::monostate,
		std::int32_t a_value)
	{
		return std::signbit(a_value) ? -1 : 1;
	}

	static std::int32_t SignF(std::monostate,
		double a_value)
	{
		return std::signbit(a_value) ? -1 : 1;
	}

	static std::int32_t CopySign(std::monostate,
		std::int32_t a_magnitude,
		std::int32_t a_sign)
	{
		return static_cast<std::int32_t>(std::copysign(a_magnitude, a_sign));
	}

	static double CopySignF(std::monostate,
		double a_magnitude,
		double a_sign)
	{
		return std::copysign(a_magnitude, a_sign);
	}

	static double Ceil(std::monostate,
		double a_value)
	{
		return std::ceil(a_value);
	}

	static double Floor(std::monostate,
		double a_value)
	{
		return std::floor(a_value);
	}

	static double Round(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		double a_value,
		std::int32_t a_decimals)
	{
		constexpr auto MIN_DECIMALS = 0;
		constexpr auto MAX_DECIMALS = std::numeric_limits<float>::digits10;

		if (a_decimals < MIN_DECIMALS || a_decimals > MAX_DECIMALS) {
			a_vm.PostError(fmt::format("The decimals must be between {} and {} (inclusive)", MIN_DECIMALS, MAX_DECIMALS),
				a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return 0.0;
		}

		if (a_decimals == 0) {
			return std::round(a_value);
		}

		const auto factor = std::pow(10, a_decimals);
		return std::round(a_value * factor) / factor;
	}

	static double Trunc(std::monostate,
		double a_value)
	{
		return std::trunc(a_value);
	}

	static double Lerp(std::monostate,
		double a_start,
		double a_end,
		double a_alpha)
	{
		return (a_start * (1.0 - a_alpha)) + (a_end * a_alpha);
	}

	static std::int32_t LCM(std::monostate,
		std::int32_t a_left,
		std::int32_t a_right)
	{
		return std::lcm(a_left, a_right);
	}

	static std::int32_t GCD(std::monostate,
		std::int32_t a_left,
		std::int32_t a_right)
	{
		return std::gcd(a_left, a_right);
	}

	static double Pow(std::monostate,
		double a_base,
		double a_exponent)
	{
		return std::pow(a_base, a_exponent);
	}

	static double Sqrt(std::monostate,
		double a_value)
	{
		return std::sqrt(a_value);
	}

	static double Exp(std::monostate,
		double a_value)
	{
		return std::exp(a_value);
	}

	static double Log(std::monostate,
		double a_value)
	{
		return std::log(a_value);
	}

	static double LogN(std::monostate,
		double a_base,
		double a_value)
	{
		return std::log(a_value) / std::log(a_base);
	}

	static double DegToRad(std::monostate,
		double a_value)
	{
		return a_value * std::numbers::pi_v<double> / 180.0;
	}

	static double RadToDeg(std::monostate,
		double a_value)
	{
		return a_value * 180.0 / std::numbers::pi_v<double>;
	}

	static double Cbrt(std::monostate,
		double a_value)
	{
		return std::cbrt(a_value);
	}

	static double Hypot(std::monostate,
		double a_x,
		double a_y)
	{
		return std::hypot(a_x, a_y);
	}

	static double Sin(std::monostate,
		double a_value)
	{
		return std::sin(a_value);
	}

	static double Cos(std::monostate,
		double a_value)
	{
		return std::cos(a_value);
	}

	double Tan(std::monostate,
		double a_value)
	{
		return std::tan(a_value);
	}

	static double Sinh(std::monostate,
		double a_value)
	{
		return std::sinh(a_value);
	}

	static double Cosh(std::monostate,
		double a_value)
	{
		return std::cosh(a_value);
	}

	static double Tanh(std::monostate,
		double a_value)
	{
		return std::tanh(a_value);
	}

	static double Asin(std::monostate,
		double a_value)
	{
		return std::asin(a_value);
	}

	static double Acos(std::monostate,
		double a_value)
	{
		return std::acos(a_value);
	}

	static double Atan(std::monostate,
		double a_value)
	{
		return std::atan(a_value);
	}

	static double Atan2(std::monostate,
		double a_y,
		double a_x)
	{
		return std::atan2(a_y, a_x);
	}

	static double Asinh(std::monostate,
		double a_value)
	{
		return std::asinh(a_value);
	}

	static double Acosh(std::monostate,
		double a_value)
	{
		return std::acosh(a_value);
	}

	static double Atanh(std::monostate,
		double a_value)
	{
		return std::atanh(a_value);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Pi);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, E);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Tau);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RandomSeed);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SeededInt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SeededBool);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SeededFloat);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SeededShuffle);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Abs);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, AbsF);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Min);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, MinF);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Max);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, MaxF);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Clamp);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ClampF);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Sign);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SignF);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, CopySign);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, CopySignF);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Ceil);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Floor);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Round);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Trunc);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Lerp);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, LCM);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GCD);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Pow);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Sqrt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Exp);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Log);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, LogN);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, DegToRad);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RadToDeg);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Cbrt);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Hypot);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Sin);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Cos);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Tan);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Sinh);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Cosh);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Tanh);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Asin);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Acos);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Atan);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Atan2);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Asinh);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Acosh);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Atanh);

		return true;
	}
}
