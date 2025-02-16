#include "Internal/Bethesda/ObjectLock.hpp"

namespace Internal
{
	ObjectLock::ObjectLock(const RE::BSTSmartPointer<RE::BSScript::Object>& a_object) noexcept :
		_object(a_object)
	{
		if (!a_object) {
			assert(false);
			return;
		}

		Lock();
	}

	ObjectLock::~ObjectLock() noexcept
	{
		Unlock();
	}

	bool ObjectLock::IsLocked() const noexcept
	{
		auto mutex = GetMutex();
		if (mutex) {
			auto lock = RE::stl::atomic_ref{ mutex };
			return lock > 0;
		}

		return false;
	}

	void ObjectLock::Lock() noexcept
	{
		auto mutex = GetMutex();
		if (!mutex) {
			auto lock = RE::stl::atomic_ref{ mutex };
			lock++;
		}
	}

	void ObjectLock::Unlock() noexcept
	{
		auto mutex = GetMutex();
		if (mutex) {
			auto lock = RE::stl::atomic_ref{ mutex };
			lock--;
		}
	}

	std::uintptr_t ObjectLock::GetMutex() const noexcept
	{
		return reinterpret_cast<std::uintptr_t>(_object->lockStructure) & ~static_cast<std::uintptr_t>(1);
	}
}
