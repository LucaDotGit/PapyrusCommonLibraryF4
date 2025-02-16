#pragma once

namespace System::MiscObject
{
	static constexpr auto SCRIPT_NAME = "System:MiscObject"sv;

	static constexpr auto COMPONENTS_KEY = "Components"sv;
	static constexpr auto OBJECT_KEY = "Object"sv;
	static constexpr auto COUNT_KEY = "Count"sv;
	static constexpr auto DISPLAY_INDEX_KEY = "DisplayIndex"sv;

	using Data = RE::BSScript::structure_wrapper<"System:MiscObject", "Data">;
	using Entry = RE::BSScript::structure_wrapper<"System:MiscObject", "Entry">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectMISC* a_miscObject)
	{
		if (!a_miscObject) {
			a_vm.PostError(::Internal::Errors::MISC_OBJECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto* componentData = a_miscObject->componentData;
		const auto* displayIndexes = a_miscObject->displayIndices;

		auto data = Data();
		auto entries = std::vector<Entry>();

		if (componentData) {
			const auto size = componentData->size();
			entries.reserve(size);

			for (auto i = 0ui32; i < size; i++) {
				const auto& [object, value] = componentData->at(i);

				auto entry = Entry();
				entry.insert(OBJECT_KEY, object);
				entry.insert(COUNT_KEY, value.i);

				const auto displayIndex = displayIndexes ? displayIndexes[i] : 0;
				entry.insert(DISPLAY_INDEX_KEY, displayIndex);

				entries.push_back(std::move(entry));
			}
		}

		data.insert(COMPONENTS_KEY, std::move(entries));

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectMISC* a_miscObject,
		Data a_data)
	{
		if (!a_miscObject) {
			a_vm.PostError(::Internal::Errors::MISC_OBJECT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		const auto newComponents = a_data.find<std::vector<Entry>>(COMPONENTS_KEY).value_or(std::vector<Entry>());
		const auto newSize = static_cast<std::uint32_t>(newComponents.size());

		auto*& oldComponents = a_miscObject->componentData;
		auto*& oldIndexes = a_miscObject->displayIndices;

		if (oldComponents) {
			delete oldComponents;
			oldComponents = nullptr;
		}

		if (oldIndexes) {
			RE::free(oldIndexes);
			oldIndexes = nullptr;
		}

		if (newSize <= 0) {
			return;
		}

		oldComponents = new RE::BSTArray<RE::BSTTuple<RE::TESForm*, RE::BGSTypedFormValuePair::SharedVal>>();
		oldComponents->reserve(newSize);

		oldIndexes = RE::calloc<std::int8_t>(newSize);

		for (auto i = 0ui32; i < newSize; i++) {
			const auto& entry = newComponents[i];

			auto* object = entry.find<RE::BGSComponent*>(OBJECT_KEY).value_or(nullptr);
			auto count = entry.find<std::uint32_t>(COUNT_KEY).value_or(0);
			auto displayIndex = entry.find<std::uint8_t>(DISPLAY_INDEX_KEY).value_or(0);

			auto pair = RE::BGSTypedFormValuePair::SharedVal();
			pair.i = count;

			oldComponents->emplace_back(object, std::move(pair));
			oldIndexes[i] = displayIndex;
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}