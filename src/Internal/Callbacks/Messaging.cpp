#include "Internal/Callbacks/Messaging.hpp"

#include "Internal/Callbacks/CrosshairRefHandler.hpp"
#include "Internal/Callbacks/GameStartedHandler.hpp"
#include "Internal/Callbacks/LockpickRefHandler.hpp"

#include "Internal/Bethesda/IniSettings.hpp"
#include "Internal/Serialization/SaveVarMap.hpp"

#include "Internal/Runners/CommandRunner.hpp"
#include "Internal/Runners/FunctionRunner.hpp"
#include "Internal/Runners/TranslationRunner.hpp"

#include "Internal/Events/Sources/DeleteGameSource.hpp"
#include "Internal/Events/Sources/PostLoadGameSource.hpp"
#include "Internal/Events/Sources/PostSaveGameSource.hpp"
#include "Internal/Events/Sources/PreSaveGameSource.hpp"

namespace Internal::Messaging
{
	[[nodiscard]] static bool GetBool(const F4SE::MessagingInterface::Message* a_msg) noexcept
	{
		return a_msg->dataLen > 0 && a_msg->data != nullptr;
	}

	[[nodiscard]] static std::string_view GetStringView(const F4SE::MessagingInterface::Message* a_msg) noexcept
	{
		return { reinterpret_cast<const char*>(a_msg->data), a_msg->dataLen };
	}

	static void OnGameStart([[maybe_unused]] bool a_succeeded)
	{
		CrosshairRefHandler::GetSingleton()->Register();
		LockpickRefHandler::GetSingleton()->Register();

		FunctionRunner::Run(FunctionRunner::Event::OnGameStart);
	}

	static void OnGameLoad([[maybe_unused]] bool a_succeeded)
	{
		FunctionRunner::Run(FunctionRunner::Event::OnGameLoad);
	}

	static void OnPostGameStart([[maybe_unused]] bool a_succeeded)
	{
		CrosshairRefHandler::GetSingleton()->Clear();
		LockpickRefHandler::GetSingleton()->Clear();

		FunctionRunner::Run(FunctionRunner::Event::OnPostGameStart);
		Events::PostLoadGameSource::GetEventSource()->Notify({ a_succeeded });
	}

	void Callback(F4SE::MessagingInterface::Message* a_msg)
	{
		logger::debug("Messaging: Received message of type: {}"sv, a_msg->type);

		switch (a_msg->type) {
			case F4SE::MessagingInterface::kGameDataReady: {
				IniSettings::Setup();

				CommandRunner::Setup();
				FunctionRunner::Setup();

				TranslationRunner::Setup();
				TranslationRunner::Run();

				Serialization::SaveVarMap::GetSingleton()->Setup();
				break;
			}
			case F4SE::MessagingInterface::kGameLoaded: {
				CommandRunner::Run();
				break;
			}
			case F4SE::MessagingInterface::kNewGame:
			case F4SE::MessagingInterface::kPostLoadGame: {
				const auto isSucceeded = GetBool(a_msg);
				if (!isSucceeded) {
					break;
				}

				if (GameStartedHandler::IsGameStarted) {
					GameStartedHandler::IsPostGameStart = true;
					OnPostGameStart(isSucceeded);
				}
				else {
					GameStartedHandler::IsGameStarted = true;
					OnGameStart(isSucceeded);
				}

				OnGameLoad(isSucceeded);
				break;
			}
			case F4SE::MessagingInterface::kPreSaveGame: {
				const auto saveName = GetStringView(a_msg);
				Events::PreSaveGameSource::GetEventSource()->Notify({ saveName });
				break;
			}
			case F4SE::MessagingInterface::kPostSaveGame: {
				const auto saveName = GetStringView(a_msg);
				Events::PostSaveGameSource::GetEventSource()->Notify({ saveName });
				break;
			}
			case F4SE::MessagingInterface::kDeleteGame: {
				const auto saveName = GetStringView(a_msg);
				Events::DeleteGameSource::GetEventSource()->Notify({ saveName });
				break;
			}
		}
	}
}
