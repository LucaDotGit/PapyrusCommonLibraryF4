#include "Internal/Serialization/Registration.hpp"

#include "Internal/Serialization/SaveVarMap.hpp"
#include "Internal/Serialization/StringMap.hpp"

namespace Internal::Serialization
{
	static constexpr auto ID = static_cast<std::uint32_t>('PCL_');

	void Setup(const F4SE::SerializationInterface* a_interface)
	{
		logger::debug("Serialization: Setup"sv);

		a_interface->SetUniqueID(ID);
		a_interface->SetSaveCallback(Save);
		a_interface->SetLoadCallback(Load);
		a_interface->SetRevertCallback(Revert);
	}

	void Load(const F4SE::SerializationInterface* a_interface)
	{
		logger::debug("Serialization: Loading"sv);

		auto recordType = 0ui32;
		auto recordVersion = 0ui32;
		auto recordLength = 0ui32;

		while (a_interface->GetNextRecordInfo(recordType, recordVersion, recordLength)) {
			if (StringMap::Load(a_interface, recordType, recordVersion, recordLength) ||
				SaveVarMap::GetSingleton()->Load(a_interface, recordType, recordVersion, recordLength)) {
				continue;
			}
		}
	}

	void Save(const F4SE::SerializationInterface* a_interface)
	{
		logger::debug("Serialization: Saving"sv);

		SaveVarMap::GetSingleton()->Hash();
		StringMap::Save(a_interface);

		SaveVarMap::GetSingleton()->Save(a_interface);
		StringMap::Revert(a_interface);
	}

	void Revert(const F4SE::SerializationInterface* a_interface)
	{
		logger::debug("Serialization: Reverting"sv);

		StringMap::Revert(a_interface);
		SaveVarMap::GetSingleton()->Revert(a_interface);
	}
}
