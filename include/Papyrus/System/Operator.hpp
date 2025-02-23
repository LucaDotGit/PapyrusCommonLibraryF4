#pragma once

namespace System::Operator
{
	static constexpr auto SCRIPT_NAME = "System:Operator"sv;

	static const RE::BSScript::Variable* Copy(std::monostate,
		const RE::BSScript::Variable* a_var)
	{
		return ::Internal::Copier::CopyVar(a_var);
	}

	static const RE::BSScript::Variable* DeepCopy(std::monostate,
		const RE::BSScript::Variable* a_var)
	{
		return ::Internal::Copier::DeepCopyVar(a_var);
	}

	static bool IsNone(std::monostate,
		const RE::BSScript::Variable* a_var)
	{
		return !a_var || !*a_var;
	}

	static bool IsStruct(std::monostate,
		const RE::BSScript::Variable* a_var)
	{
		return a_var && a_var->is<RE::BSScript::Struct>();
	}

	static bool IsArray(std::monostate,
		const RE::BSScript::Variable* a_var)
	{
		return a_var && a_var->is<RE::BSScript::Array>();
	}

	static bool Equals(std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right)
	{
		return ::Internal::Comparer::Equals(a_left, a_right);
	}

	static bool RefEquals(std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right)
	{
		return ::Internal::Comparer::RefEquals(a_left, a_right);
	}

	static bool TypeEquals(std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right)
	{
		return ::Internal::Comparer::TypeEquals(a_left, a_right);
	}

	static std::int32_t Compare(std::monostate,
		const RE::BSScript::Variable* a_left,
		const RE::BSScript::Variable* a_right)
	{
		return ::Internal::Comparer::Compare(a_left, a_right)._Value;
	}

	static RE::BSScript::TypeInfo::RawType GetRawType(std::monostate,
		const RE::BSScript::Variable* a_var)
	{
		return ::Internal::Comparer::GetRawType(a_var);
	}

	static std::int32_t Mod(std::monostate,
		std::int32_t a_left,
		std::int32_t a_right)
	{
		return a_left % a_right;
	}

	static float ModF(std::monostate,
		float a_left,
		float a_right)
	{
		return std::fmod(a_left, a_right);
	}

	static std::uint32_t LShift(std::monostate,
		std::uint32_t a_left,
		std::uint32_t a_right)
	{
		return a_left << a_right;
	}

	static std::uint32_t RShift(std::monostate,
		std::uint32_t a_left,
		std::uint32_t a_right)
	{
		return a_left >> a_right;
	}

	static std::uint32_t AND(std::monostate,
		std::uint32_t a_left,
		std::uint32_t a_right)
	{
		return a_left & a_right;
	}

	static std::uint32_t OR(std::monostate,
		std::uint32_t a_left,
		std::uint32_t a_right)
	{
		return a_left | a_right;
	}

	static std::uint32_t XOR(std::monostate,
		std::uint32_t a_left,
		std::uint32_t a_right)
	{
		return a_left ^ a_right;
	}

	static std::uint32_t NOT(std::monostate,
		std::uint32_t a_value)
	{
		return ~a_value;
	}

	static bool HasFlag(std::monostate,
		std::uint32_t a_value,
		std::uint32_t a_flag)
	{
		return a_value & a_flag;
	}

	static std::uint32_t SetFlag(std::monostate,
		std::uint32_t a_value,
		std::uint32_t a_flag,
		bool a_set)
	{
		return a_set ? (a_value | a_flag) : (a_value & ~a_flag);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Copy);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, DeepCopy);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsNone);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsStruct);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, IsArray);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Equals);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RefEquals);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, TypeEquals);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Compare);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, GetRawType);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, Mod);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, ModF);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, LShift);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, RShift);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, AND);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, OR);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, XOR);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, NOT);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, HasFlag);
		BIND_METHOD_SAFE(a_vm, SCRIPT_NAME, SetFlag);

		return true;
	}
}
