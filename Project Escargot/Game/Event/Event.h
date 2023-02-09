#pragma once

// Customize your Event type here
#define EVENTID std::string
#include <string>

namespace Snail
{
    class Event {
    private:
        // Members
        EVENTID eventId;
        void* parameter;

    public:
        // Constructor
        Event(EVENTID eventId, void* parameter = 0) {
            this->eventId = eventId;
            this->parameter = parameter;
        }

        // Destructor
        ~Event() {}

        // Accessors
        inline EVENTID EventId() const { return eventId; }
        inline void* Parameter() { return parameter; }
    };
}