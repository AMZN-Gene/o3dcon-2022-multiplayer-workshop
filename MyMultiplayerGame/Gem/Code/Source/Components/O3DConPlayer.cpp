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
        if (IsNetEntityRoleAutonomous())
        {
            InputChannelEventListener::Connect();
        }
    }

    void O3DConPlayerController::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
        if (IsNetEntityRoleAutonomous())
        {
            InputChannelEventListener::Disconnect();
        }
    }

    void O3DConPlayerController::CreateInput([[maybe_unused]] Multiplayer::NetworkInput& input, [[maybe_unused]] float deltaTime)
    {
        O3DConPlayerNetworkInput* playerInput = input.FindComponentInput<O3DConPlayerNetworkInput>();
        playerInput->m_buttonsMashed = m_keysPressed;
        m_keysPressed = 0;
    }

    void O3DConPlayerController::ProcessInput([[maybe_unused]] Multiplayer::NetworkInput& input, [[maybe_unused]] float deltaTime)
    {
        const auto* playerInput = input.FindComponentInput<O3DConPlayerNetworkInput>();

        if (playerInput->m_buttonsMashed > 0)
        {
            AZLOG_WARN("Player pressed %i keys this network frame!", playerInput->m_buttonsMashed);
        }
    }

    bool O3DConPlayerController::OnInputChannelEventFiltered(const AzFramework::InputChannel& inputChannel)
    {
        // only accept keyboard input
        if (inputChannel.GetInputDevice().GetInputDeviceId().GetNameCrc32() != AZ_CRC("keyboard"))
        {
            return false;
        }

        const bool isPressed = inputChannel.GetValue() > 0.0f;
        if (!m_isPressing && isPressed)
        {
            m_isPressing = true;
            ++m_keysPressed;
        }
        else if (inputChannel.GetValue() == 0.0f)
        {
            m_isPressing = false;
        }

        return true;
    }
}