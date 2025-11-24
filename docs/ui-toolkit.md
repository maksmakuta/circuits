# Building UIs with widgets

Circuits ships a small declarative widget set so you can build screens without writing low-level drawing code. Each widget implements `IWidget` with `onDraw`, `onUpdate`, and `onEvent` hooks.

## Constructing widgets
Include `ui/UI.h` and use the factory helpers to build a hierarchy:
```cpp
using namespace circuits;
WidgetPtr layout = column({
    label("Welcome", {.padding = {16, 8}}),
    button("Continue", {.padding = {16, 8}}),
    toggle(false, {.padding = {16, 8}})
}, {.padding = {24, 24}});
```

Common factories:
- `label(text, mod)`
- `button(inner|text, mod)`
- `input(text, mod)`
- `toggle(state, mod)`
- `image(texture, mod)`
- `card(inner, mod)`, `tooltip(inner, mod)`, `notification(message, mod)`
- Layout: `column(children, mod)`, `row(children, mod)`, `grid(children, mod)`, `box(children, mod)`

## Layout and modifiers
The `Modifier` argument customizes sizing and positioning:
- `size`, `width`, `height` for fixed dimensions.
- `asParent`/`asWidth`/`asHeight` to size relative to the parent.
- `padding` to inset content.
- `gravity` to align a child within its available space.

Place modifiers on both the container and children to achieve the layout you need.

## Handling input
Buttons, toggles, and other interactive widgets rely on mouse events. In your screen's `onEvent`, forward events to the layout root so it can update hover/active state:
```cpp
void MyScreen::onEvent(const Event& e) {
    m_root->onEvent(e); // where m_root is your top-level WidgetPtr
}
```

## Updating and drawing
Call `m_root->onUpdate(delta)` each frame, then `m_root->onDraw(renderer)` inside `IScreen::onDraw`. Widgets use `ThemeManager` to pick colors, fonts, and radii, so your UI inherits the current light/dark theme automatically.
