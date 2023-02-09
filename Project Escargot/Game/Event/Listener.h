#pragma once

namespace Snail
{
    class Listener {
    public:
        // Constructor
        Listener() {}
        // Destructor
        virtual ~Listener() {}
        // Handles the event passed to it
        virtual void HandleEvent(Event* event) = 0;
    };
}