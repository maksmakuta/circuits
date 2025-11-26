#include "Event.h"

#include <SDL3/SDL_events.h>

namespace circuits {

    Event Event::WindowClose() {
        Event e;
        e.type = EventType::WindowClose;
        return e;
    }

    Event Event::WindowResize(const int w, const int h) {
        Event e;
        e.type = EventType::WindowResize;
        e.window = { w, h };
        return e;
    }

    Event Event::KeyDown(const unsigned key, const bool repeat, const Mods mods) {
        Event e;
        e.type = EventType::KeyDown;
        e.key = { key, repeat };
        e.mods = mods;
        return e;
    }

    Event Event::KeyUp(const unsigned key, const Mods mods) {
        Event e;
        e.type = EventType::KeyUp;
        e.key = { key, false };
        e.mods = mods;
        return e;
    }

    Event Event::MouseMove(const float x, const float y, const float dx, const float dy, const Mods mods) {
        Event e;
        e.type = EventType::MouseMove;
        e.mouseMove = { x, y, dx, dy };
        e.mods = mods;
        return e;
    }

    Event Event::MouseDown(const unsigned button, const float x, const float y, const Mods mods) {
        Event e;
        e.type = EventType::MouseDown;
        e.mouseButton = { x, y, button };
        e.mods = mods;
        return e;
    }

    Event Event::MouseUp(const unsigned button, const float x, const float y, const Mods mods) {
        Event e;
        e.type = EventType::MouseUp;
        e.mouseButton = { x, y, button };
        e.mods = mods;
        return e;
    }

    Event Event::MouseWheel(const float dx, const float dy, const Mods mods) {
        Event e;
        e.type = EventType::MouseWheel;
        e.mouseWheel = { dx, dy };
        e.mods = mods;
        return e;
    }

    Event Event::Recompose(){
        Event e;
        e.type = EventType::Recompose;
        return e;
    }

    void pushEvent(Event ev) {
        auto* copy = new Event(ev);
        SDL_Event e{};
        e.type = SDL_EVENT_USER;
        e.user.code = static_cast<int>(ev.type);
        e.user.data1 = copy;
        e.user.data2 = nullptr;
        SDL_PushEvent(&e);
    }
}
