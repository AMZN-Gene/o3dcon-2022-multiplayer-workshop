#pragma once

#include <Source/AutoGen/O3DConPlayer.AutoComponent.h>
#include <AzFramework/Input/Events/InputChannelEventListener.h>

namespace MyMultiplayerGame
{
    class O3DConPlayerController
        : public O3DConPlayerControllerBase
        , AzFramework::InputChannelEventListener // In a real game it would be wiser to use StartingPointInput::InputEventNotificationBus::MultiHandler instead
    {
    public:
        explicit O3DConPlayerController(O3DConPlayer& parent);

        void OnActivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating entityIsMigrating) override;

        //! Common input creation logic for the NetworkInput.
        //! Fill out the input struct and the MultiplayerInputDriver will send the input data over the network
        //!    to ensure it's processed.
        //! @param input  input structure which to store input data for sending to the authority
        //! @param deltaTime amount of time to integrate the provided inputs over
        void CreateInput(Multiplayer::NetworkInput& input, float deltaTime) override;

        //! Common input processing logic for the NetworkInput.
        //! @param input  input structure to process
        //! @param deltaTime amount of time to integrate the provided inputs over
        void ProcessInput(Multiplayer::NetworkInput& input, float deltaTime) override;

        //! AzFramework::InputChannelEventListener overrides
        bool OnInputChannelEventFiltered(const AzFramework::InputChannel& inputChannel) override;

    private:
        int m_keysPressed = 0;
        bool m_isPressing = false;
    };
}