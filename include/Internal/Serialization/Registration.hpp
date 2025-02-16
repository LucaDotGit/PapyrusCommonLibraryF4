#pragma once

namespace Internal::Serialization
{
	void Setup(const F4SE::SerializationInterface* a_interface);
	void Load(const F4SE::SerializationInterface* a_interface);
	void Save(const F4SE::SerializationInterface* a_interface);
	void Revert(const F4SE::SerializationInterface* a_interface);
}
