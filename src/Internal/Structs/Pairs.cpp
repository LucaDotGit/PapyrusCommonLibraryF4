#include "Internal/Structs/Pairs.hpp"

namespace Internal::Pairs
{
	static constexpr auto NAME_KEY = "Name"sv;
	static constexpr auto VALUE_KEY = "Value"sv;

	Pair MakePair(std::string_view a_name, const RE::BSScript::Variable* a_value) noexcept
	{
		auto pair = Pair();
		SetPair(pair, a_name, a_value);
		return pair;
	}

	StringPair MakeStringPair(std::string_view a_name, std::string_view a_value) noexcept
	{
		auto pair = StringPair();
		SetStringPair(pair, a_name, a_value);
		return pair;
	}

	std::tuple<RE::BSFixedString, const RE::BSScript::Variable*> GetPair(const Pair& a_pair) noexcept
	{
		return std::make_tuple(
			GetName(a_pair),
			GetValue(a_pair));
	}

	bool SetPair(Pair& a_pair, std::string_view a_name, const RE::BSScript::Variable* a_value) noexcept
	{
		return SetName(a_pair, a_name) &&
			   SetValue(a_pair, a_value);
	}

	std::tuple<RE::BSFixedString, RE::BSFixedString> GetStringPair(const StringPair& a_pair) noexcept
	{
		return std::make_tuple(
			GetName(a_pair),
			GetValue(a_pair));
	}

	bool SetStringPair(StringPair& a_pair, std::string_view a_name, std::string_view a_value) noexcept
	{
		return SetName(a_pair, a_name) &&
			   SetValue(a_pair, a_value);
	}

	RE::BSFixedString GetName(const Pair& a_pair) noexcept
	{
		return a_pair.find<RE::BSFixedString>(NAME_KEY).value_or(RE::BSFixedString());
	}

	bool SetName(Pair& a_pair, std::string_view a_name) noexcept
	{
		return a_pair.insert(NAME_KEY, a_name);
	}

	RE::BSFixedString GetName(const StringPair& a_pair) noexcept
	{
		return a_pair.find<RE::BSFixedString>(NAME_KEY).value_or(RE::BSFixedString());
	}

	bool SetName(StringPair& a_pair, std::string_view a_name) noexcept
	{
		return a_pair.insert(NAME_KEY, a_name);
	}

	const RE::BSScript::Variable* GetValue(const Pair& a_pair) noexcept
	{
		return a_pair.find<const RE::BSScript::Variable*>(VALUE_KEY).value_or(nullptr);
	}

	bool SetValue(Pair& a_pair, const RE::BSScript::Variable* a_value) noexcept
	{
		return a_pair.insert(VALUE_KEY, a_value);
	}

	RE::BSFixedString GetValue(const StringPair& a_pair) noexcept
	{
		return a_pair.find<RE::BSFixedString>(VALUE_KEY).value_or(RE::BSFixedString());
	}

	bool SetValue(StringPair& a_pair, std::string_view a_value) noexcept
	{
		return a_pair.insert(VALUE_KEY, a_value);
	}
}
