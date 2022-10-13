#include <Source/Components/O3DConPlayer.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzFramework/Entity/EntityDebugDisplayBus.h>

namespace MyMultiplayerGame
{
    // Component logic is ran anywhere this entity exists; on server and for all clients
    void O3DConPlayer::Reflect(AZ::ReflectContext* context)
    {
        AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context);
        if (serializeContext)
        {
            serializeContext->Class<O3DConPlayer, O3DConPlayerBase>()
                ->Version(1);
        }
        O3DConPlayerBase::Reflect(context);
    }

    void O3DConPlayer::OnInit()
    {
    }

    void O3DConPlayer::OnActivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
        AZ::TickBus::Handler::BusConnect();
    }

    void O3DConPlayer::OnDeactivate([[maybe_unused]] Multiplayer::EntityIsMigrating entityIsMigrating)
    {
        AZ::TickBus::Handler::BusDisconnect();
    }

    void O3DConPlayer::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
        AZStd::string playerId = AZStd::string::format("Player: %i", GetPlayerId());
        AzFramework::DebugDisplayRequestBus::Broadcast(&AzFramework::DebugDisplayRequests::SetColor, AZ::Colors::Cornsilk);
        AzFramework::DebugDisplayRequestBus::Broadcast(&AzFramework::DebugDisplayRequests::DrawTextLabel, GetEntity()->GetTransform()->GetWorldTranslation(), 0.7f, playerId.c_str(), true, 0, 0);
    }

    // Controller logic; only ran in where we have ownership of this entity. 
    // Ran for the authority (server) and on clients but only in the special case of autonomous players.
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
        else if (IsNetEntityRoleAuthority())
        {
            const int playerId = static_cast<int>(AZ::Interface<Multiplayer::IMultiplayer>::Get()->GetStats().m_clientConnectionCount);
            SetPlayerId(playerId);
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
        const AZ::Vector3 MovementPerButtonPress = AZ::Vector3::CreateAxisY(10.0f);
        const AZ::Vector3 delta = MovementPerButtonPress * aznumeric_cast<float>(playerInput->m_buttonsMashed);
        GetNetworkCharacterComponentController()->TryMoveWithVelocity(delta, deltaTime);
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