# Windowing and event handling

Circuits wraps SDL3 for cross-platform window and input handling.

## Creating and controlling the window
- By default, `Application` constructs a `Window` with the title "Circuits" and a preset size. Use `Window::setTitle`, `move`, or `resize` if you need to change these at runtime.
- Call `Window::close()` to request shutdown. The main loop in `Application::run()` exits once `isClosed()` becomes `true`.

## Receiving events
- `Window::poll(Event&)` fetches pending input; `Application` already calls it every frame and forwards events to the active screen.
- Handle events inside `IScreen::onEvent(const Event&)` or custom widgets. Event types include `KeyDown`/`KeyUp`, `MouseMove`, `MouseDown`/`MouseUp`, `MouseWheel`, `WindowClose`, and `WindowResize` (see `window/Event.h`).
- Modifier keys arrive in `Event::mods` (`shift`, `ctrl`, `alt`). Mouse events provide coordinates relative to the window.

## Typical pattern
```cpp
void MyScreen::onEvent(const Event& e) {
    switch (e.type) {
        case EventType::MouseDown:
            // hit-test your widget tree and update state
            break;
        case EventType::WindowResize:
            // pass the new size to your layout root if needed
            break;
        default:
            break;
    }
}
```

Screens usually update their widget tree in response to events and let `Renderer` draw the resulting state during `onDraw`.
