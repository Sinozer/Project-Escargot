#include "stdafx.h"

namespace Snail
{
    InputListener::InputListener() {
        EventSystem::Instance()->RegisterClient("PLAYER_JUMP", this);
        EventSystem::Instance()->RegisterClient("PLAYER_SHOOT", this);
        resting = false;
    }

    InputListener::~InputListener() {

    }

    void InputListener::HandleEvent(Event* event) {
        if (event != nullptr) {
            // Player jumped?
            if (event->EventId() == "PLAYER_JUMP") {
                std::cout << "Player Jumped.\n";
            }
            // Player fired?
            else if (event->EventId() == "PLAYER_SHOOT") {
                std::cout << "Player Shot\n";
            }
            else {
                resting = true;
            }
        }
    }
}