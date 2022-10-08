#include <Source/Components/O3DConPlayer.h>

#include <AzCore/Serialization/SerializeContext.h>

namespace MyMultiplayerGame
{
    O3DConPlayerController::O3DConPlayerController(O3DConPlayer& parent)
        : O3DConPlayerControllerBase(parent)
    {
    }

    void O3DConPlayerController::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    void O3DConPlayerController::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
    }

    void O3DConPlayerController::CreateInput([[maybe_unused]] Multiplayer::NetworkInput& input, [[maybe_unused]] float deltaTime)
    {
    }

    void O3DConPlayerController::ProcessInput([[maybe_unused]] Multiplayer::NetworkInput& input, [[maybe_unused]] float deltaTime)
    {
    }
}