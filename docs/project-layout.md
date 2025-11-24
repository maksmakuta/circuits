# Project layout

Use this map to locate the pieces you will customize when building on Circuits:

- `src/main.cpp`: entry point that launches `circuits::Application`.
- `src/simulator/Application.*`: main loop, event polling, and the active screen slot.
- `src/simulator/screen/`: example screens (`MainScreen`) you can copy or replace.
- `src/ui/`: widget implementations, layout helpers, and the `ui/UI.h` factories.
- `src/ui/theme/`: theming and `ThemeManager` utilities.
- `src/graphics/`: `Renderer` and drawing primitives.
- `src/window/`: SDL3-based window and event types.
- `libs/`: vendored dependencies such as GLAD and LodePNG.
- `docs/`: this user documentation set.
