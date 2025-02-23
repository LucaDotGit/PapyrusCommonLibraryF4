#include "Internal/Structs/MagicItem.hpp"

namespace Internal::MagicItem
{
	static constexpr auto EFFECT_KEY = "Effect"sv;
	static constexpr auto MAGNITUDE_KEY = "Magnitude"sv;
	static constexpr auto AREA_KEY = "Area"sv;
	static constexpr auto DURATION_KEY = "Duration"sv;

	std::vector<Entry> GetEntries(const RE::MagicItem* a_magicItem) noexcept
	{
		const auto& oldEntries = a_magicItem->listOfEffects;

		auto entries = std::vector<Entry>();
		entries.reserve(oldEntries.size());

		for (const auto* element : oldEntries) {
			if (!element) {
				continue;
			}

			const auto& elementData = element->data;

			auto entry = Entry();
			entry.insert(EFFECT_KEY, element->effectSetting);
			entry.insert(MAGNITUDE_KEY, elementData.magnitude);
			entry.insert(AREA_KEY, elementData.area);
			entry.insert(DURATION_KEY, elementData.duration);

			entries.push_back(std::move(entry));
		}

		return entries;
	}

	void SetEntries(RE::MagicItem* a_magicItem, const std::vector<Entry>& a_entries) noexcept
	{
		auto& oldEntries = a_magicItem->listOfEffects;

		const auto oldSize = oldEntries.size();
		const auto newSize = a_entries.size();

		for (auto i = oldSize; i > newSize; i--) {
			auto*& element = oldEntries[i - 1];
			if (!element) {
				continue;
			}

			delete element;
			element = nullptr;
		}

		oldEntries.resize(static_cast<std::uint32_t>(newSize));

		for (auto i = 0ui32; i < newSize; i++) {
			const auto& entry = a_entries[i];
			if (!entry) {
				continue;
			}

			auto*& element = oldEntries[i];
			if (!element) {
				element = new RE::EffectItem();
			}

			auto& effectData = element->data;

			element->effectSetting = entry.find<RE::EffectSetting*>(EFFECT_KEY).value_or(nullptr);
			effectData.magnitude = entry.find<float>(MAGNITUDE_KEY).value();
			effectData.area = entry.find<std::int32_t>(AREA_KEY).value();
			effectData.duration = entry.find<std::int32_t>(DURATION_KEY).value();
		}
	}
}
