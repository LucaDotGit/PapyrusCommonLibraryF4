#pragma once

namespace Internal::Pairs
{
	using Pair = RE::BSScript::structure_wrapper<"System:Pairs", "Pair">;
	using StringPair = RE::BSScript::structure_wrapper<"System:Pairs", "StringPair">;

	[[nodiscard]] Pair MakePair(std::string_view a_name, const RE::BSScript::Variable* a_value) noexcept;
	[[nodiscard]] StringPair MakeStringPair(std::string_view a_name, std::string_view a_value) noexcept;

	[[nodiscard]] std::tuple<RE::BSFixedString, const RE::BSScript::Variable*> GetPair(const Pair& a_pair) noexcept;
	bool SetPair(Pair& a_pair, std::string_view a_name, const RE::BSScript::Variable* a_value) noexcept;

	[[nodiscard]] std::tuple<RE::BSFixedString, RE::BSFixedString> GetStringPair(const StringPair& a_pair) noexcept;
	bool SetStringPair(StringPair& a_pair, std::string_view a_name, std::string_view a_value) noexcept;

	[[nodiscard]] RE::BSFixedString GetName(const Pair& a_pair) noexcept;
	bool SetName(Pair& a_pair, std::string_view a_name) noexcept;

	[[nodiscard]] RE::BSFixedString GetName(const StringPair& a_pair) noexcept;
	bool SetName(StringPair& a_pair, std::string_view a_name) noexcept;

	[[nodiscard]] const RE::BSScript::Variable* GetValue(const Pair& a_pair) noexcept;
	bool SetValue(Pair& a_pair, const RE::BSScript::Variable* a_value) noexcept;

	[[nodiscard]] RE::BSFixedString GetValue(const StringPair& a_pair) noexcept;
	bool SetValue(StringPair& a_pair, std::string_view a_value) noexcept;
}
