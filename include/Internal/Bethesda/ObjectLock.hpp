#pragma once

namespace Internal
{
	class ObjectLock final
	{
	public:
		ObjectLock(const RE::BSTSmartPointer<RE::BSScript::Object>& a_object) noexcept;
		~ObjectLock() noexcept;

	public:
		[[nodiscard]] bool IsLocked() const noexcept;

		void Lock() noexcept;
		void Unlock() noexcept;

	private:
		[[nodiscard]] std::uintptr_t GetMutex() const noexcept;

	private:
		const RE::BSTSmartPointer<RE::BSScript::Object> _object;
	};
}
