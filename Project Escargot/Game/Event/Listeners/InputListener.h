#pragma once

// If you respond to events, you must inherit from Listener

namespace Snail
{
    class InputListener : public Listener
    {
    private:
        bool resting;
    public:
        InputListener();
        ~InputListener();
        bool Resting() const { return resting; }
        // Listeners must implement the HandleEvent(Event*) method
        void HandleEvent(Event* event);
    };
}

