#pragma once

namespace System::Container
{
	static constexpr auto SCRIPT_NAME = "System:Container"sv;

	static constexpr auto FORM_FLAGS_KEY = "FormFlags"sv;
	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto OPEN_SOUND_KEY = "OpenSound"sv;
	static constexpr auto CLOSE_SOUND_KEY = "CloseSound"sv;
	static constexpr auto TAKE_ALL_SOUND_KEY = "TakeAllSound"sv;
	static constexpr auto ITEMS_KEY = "Items"sv;
	static constexpr auto ITEM_KEY = "Item"sv;
	static constexpr auto COUNT_KEY = "Count"sv;
	static constexpr auto OWNER_KEY = "Owner"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Container", "Data">;
	using Entry = RE::BSScript::structure_wrapper<"System:Container", "Entry">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectCONT* a_container)
	{
		if (!a_container) {
			a_vm.PostError(::Internal::Errors::CONTAINER_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		auto data = Data();
		data.insert(FORM_FLAGS_KEY, a_container->formFlags);
		data.insert(FLAGS_KEY, a_container->data.contFlags.underlying());
		data.insert(OPEN_SOUND_KEY, a_container->openSound);
		data.insert(CLOSE_SOUND_KEY, a_container->closeSound);
		data.insert(TAKE_ALL_SOUND_KEY, a_container->takeAllSound);

		const auto size = a_container->numContainerObjects;

		auto entries = std::vector<Entry>();
		entries.reserve(size);

		for (auto i = 0ui32; i < size; i++) {
			const auto* object = a_container->containerObjects[i];
			if (!object) {
				continue;
			}

			const auto* extraData = object->itemExtra;

			auto entry = Entry();
			entry.insert(ITEM_KEY, object->obj);
			entry.insert(COUNT_KEY, object->count);
			entry.insert(OWNER_KEY, extraData ? extraData->ownerForm : nullptr);

			entries.push_back(std::move(entry));
		}

		data.insert(ITEMS_KEY, std::move(entries));
		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectCONT* a_container,
		Data a_data)
	{
		if (!a_container) {
			a_vm.PostError(::Internal::Errors::CONTAINER_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		a_container->data.contFlags = a_data.find<RE::CONT_DATA::Flags>(FLAGS_KEY).value();
		a_container->openSound = a_data.find<RE::BGSSoundDescriptorForm*>(OPEN_SOUND_KEY).value_or(nullptr);
		a_container->closeSound = a_data.find<RE::BGSSoundDescriptorForm*>(CLOSE_SOUND_KEY).value_or(nullptr);
		a_container->takeAllSound = a_data.find<RE::BGSSoundDescriptorForm*>(TAKE_ALL_SOUND_KEY).value_or(nullptr);

		const auto newEntries = a_data.find<std::vector<Entry>>(ITEMS_KEY).value_or(std::vector<Entry>());
		const auto newSize = static_cast<std::uint32_t>(newEntries.size());

		auto**& oldEntries = a_container->containerObjects;
		auto& oldSize = a_container->numContainerObjects;

		if (oldEntries) {
			for (auto i = 0ui32; i < oldSize; i++) {
				auto*& entry = oldEntries[i];
				if (!entry) {
					continue;
				}

				auto*& itemExtra = entry->itemExtra;
				if (itemExtra) {
					delete itemExtra;
					itemExtra = nullptr;
				}

				delete entry;
				entry = nullptr;
			}

			RE::free(oldEntries);
			oldEntries = nullptr;
		}

		if (newSize > 0) {
			oldEntries = RE::calloc<RE::ContainerObject*>(newSize);

			for (auto i = 0ui32; i < newSize; i++) {
				const auto& entry = newEntries[i];
				if (!entry) {
					continue;
				}

				auto* object = entry.find<RE::TESBoundObject*>(ITEM_KEY).value_or(nullptr);
				auto count = entry.find<std::int32_t>(COUNT_KEY).value();
				auto* owner = entry.find<RE::TESForm*>(OWNER_KEY).value_or(nullptr);

				oldEntries[i] = new RE::ContainerObject(object, count, owner);
			}
		}

		oldSize = newSize;

		const auto formFlags = a_data.find<std::uint32_t>(FORM_FLAGS_KEY).value();
		if (formFlags != a_container->formFlags) {
			a_container->formFlags = formFlags;
			a_container->AddChange(RE::CHANGE_TYPE::kFormFlags);
		}
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}