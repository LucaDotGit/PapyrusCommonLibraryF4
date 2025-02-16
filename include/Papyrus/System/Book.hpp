#pragma once

namespace System::Book
{
	static constexpr auto SCRIPT_NAME = "System:Book"sv;

	static constexpr auto FLAGS_KEY = "Flags"sv;
	static constexpr auto TEXT_OFFSET_X_KEY = "TextOffsetX"sv;
	static constexpr auto TEXT_OFFSET_Y_KEY = "TextOffsetY"sv;
	static constexpr auto INVENTORY_MODEL_KEY = "InventoryModel"sv;

	using Data = RE::BSScript::structure_wrapper<"System:Book", "Data">;

	static Data GetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectBOOK* a_book)
	{
		if (!a_book) {
			a_vm.PostError(::Internal::Errors::BOOK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return nullptr;
		}

		const auto& bookData = a_book->data;

		auto data = Data();
		data.insert(FLAGS_KEY, bookData.flags.underlying());
		data.insert(TEXT_OFFSET_X_KEY, bookData.textOffsetX);
		data.insert(TEXT_OFFSET_Y_KEY, bookData.textOffsetY);
		data.insert(INVENTORY_MODEL_KEY, a_book->inventoryModel);

		return data;
	}

	static void SetData(RE::BSScript::IVirtualMachine& a_vm, RE::VMStackID a_stackID, std::monostate,
		RE::TESObjectBOOK* a_book,
		Data a_data)
	{
		if (!a_book) {
			a_vm.PostError(::Internal::Errors::BOOK_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		if (!a_data) {
			a_vm.PostError(::Internal::Errors::STRUCT_NULL, a_stackID, RE::BSScript::ErrorLogger::Severity::kError);
			return;
		}

		auto& bookData = a_book->data;

		bookData.flags = a_data.find<RE::OBJ_BOOK::Flags>(FLAGS_KEY).value();
		bookData.textOffsetX = a_data.find<std::uint32_t>(TEXT_OFFSET_X_KEY).value();
		bookData.textOffsetY = a_data.find<std::uint32_t>(TEXT_OFFSET_Y_KEY).value();
		a_book->inventoryModel = a_data.find<RE::TESObjectSTAT*>(INVENTORY_MODEL_KEY).value_or(nullptr);
	}

	static bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		BIND_METHOD(a_vm, SCRIPT_NAME, GetData);
		BIND_METHOD(a_vm, SCRIPT_NAME, SetData);

		return true;
	}
}