#pragma once

#include "Event.h"
#include "Listener.h"
#include <list>

namespace Snail
{
    class EventSystem {
    private:
        // Database of Clients & their events
        std::multimap<EVENTID, Listener*> database;

        // List of events to be processed
        std::list<Event> currentEvents;

        // Helper Methods
        bool AlreadyRegistered(EVENTID eventId, Listener* client);
        void DispatchEvent(Event* event);

        // Singleton, deny access to constructors
        // Constructor
        EventSystem() {}
        // Copy constructor
        EventSystem(const EventSystem& rhs) {}
        // Assignment Operator
        EventSystem& operator=(const EventSystem& rhs) { return *this; }

    public:
        // Destructor
        ~EventSystem() { this->Shutdown(); }

        // Returns an instance of the Event System
        static EventSystem* Instance();

        // Registers a client to start listening for an event
        void RegisterClient(EVENTID event, Listener* client);

        // Unregisters a client from a specific event
        void UnregisterClient(EVENTID event, Listener* client);

        // Unregister a client from all events
        void UnregisterAll(Listener* client);

        // Send an event
        void SendEvent(EVENTID eventId, void* data = 0);

        // Process all events
        void ProcessEvents();

        // Clear events
        void ClearEvents();

        // Shutdown event system
        void Shutdown();
    };
}

