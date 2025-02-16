#pragma once

namespace Internal::MagicItem
{
	using Entry = RE::BSScript::structure_wrapper<"System:MagicItem", "Entry">;

	[[nodiscard]] std::vector<Entry> GetEntries(const RE::MagicItem* a_magicItem) noexcept;
	void SetEntries(RE::MagicItem* a_magicItem, const std::vector<Entry>& a_entries) noexcept;
}
