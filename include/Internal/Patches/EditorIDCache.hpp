#pragma once

namespace Internal::Patches::EditorIDCache
{
	static auto EditorIDs = std::unordered_map<std::uint32_t, RE::BSFixedString>();

	void Install() noexcept;

	static const char* GetFormEditorIDImpl(RE::TESForm* a_this);
	static bool SetFormEditorIDImpl(RE::TESForm* a_this, const char* a_editorID);

	namespace
	{
		template <class T>
			requires(std::derived_from<T, RE::TESForm> &&
					 T::FORMTYPE != RE::ENUM_FORMTYPE::kNONE)
		class Patch final
		{
		private:
			Patch() = delete;
			Patch(const Patch&) = delete;
			Patch(Patch&&) = delete;
			Patch& operator=(const Patch&) = delete;
			Patch& operator=(Patch&&) = delete;

		public:
			static void Install() noexcept
			{
				auto vtable = REL::Relocation<std::uintptr_t>{ T::VTABLE[0] };

				_GetFormEditorID = vtable.write_vfunc(0x3A, GetFormEditorID);
				_SetFormEditorID = vtable.write_vfunc(0x3B, SetFormEditorID);
			}

		private:
			static const char* GetFormEditorID(RE::TESForm* a_this)
			{
				return GetFormEditorIDImpl(a_this);
			}

			static bool SetFormEditorID(RE::TESForm* a_this, const char* a_editorID)
			{
				return SetFormEditorIDImpl(a_this, a_editorID) && _SetFormEditorID(a_this, a_editorID);
			}

		private:
			inline static auto _GetFormEditorID = REL::Relocation<decltype(&RE::TESForm::GetFormEditorID)>();
			inline static auto _SetFormEditorID = REL::Relocation<decltype(&RE::TESForm::SetFormEditorID)>();
		};
	}
}
