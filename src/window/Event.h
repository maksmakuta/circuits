#ifndef CIRCUITS_EVENT_H
#define CIRCUITS_EVENT_H

namespace circuits {

    enum class EventType {
        None = 0,

        WindowClose,
        WindowResize,

        KeyDown,
        KeyUp,

        MouseMove,
        MouseDown,
        MouseUp,
        MouseWheel
    };

    struct Modifiers {
        bool shift = false;
        bool ctrl  = false;
        bool alt   = false;
    };

    struct Event {
        Event() = default;

        EventType type = EventType::None;
        Modifiers mods;
        union {
            struct { unsigned key; bool repeat; } key;
            struct { float x, y; float dx, dy; } mouseMove;
            struct { float x, y; unsigned button; } mouseButton;
            struct { float dx, dy; } mouseWheel{0,0};
            struct { int width, height; } window;
        };

        static Event WindowClose();
        static Event WindowResize(int w, int h);

        static Event KeyDown(unsigned key, bool repeat, Modifiers mods = {});
        static Event KeyUp(unsigned key, Modifiers mods = {});

        static Event MouseMove(float x, float y, float dx, float dy, Modifiers mods = {});
        static Event MouseDown(unsigned button, float x, float y, Modifiers mods = {});
        static Event MouseUp(unsigned button, float x, float y, Modifiers mods = {});
        static Event MouseWheel(float dx, float dy, Modifiers mods = {});
    };

}

#endif //CIRCUITS_EVENT_H