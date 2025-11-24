# Core concepts

Circuits provides a minimal application shell that you can customize with your own screens and widgets. Keep these concepts in mind when extending the library:

- **Application**: `circuits::Application` owns the window, renderer, and a single active screen. `main()` simply calls `Application().run()`.
- **Screens**: Implement `circuits::IScreen` to provide `onInit`, `onDeinit`, `onDraw(Renderer&)`, `onUpdate(float)`, and `onEvent(const Event&)`. Swap your screen into `Application`'s constructor to change what the user sees first.
- **Events**: All input flows through `circuits::Event` values. Screens should react in `onEvent`, updating internal state and requesting redraws through their widget tree.
- **Rendering**: The `Renderer` offers immediate-mode drawing primitives (text, shapes, textured quads) that widgets use during `onDraw`.
- **Widgets**: UI is built from `IWidget` implementations (labels, buttons, toggles, images, layout containers). Factory helpers in `ui/UI.h` keep screen code concise.

If you are building a standalone app, you can reuse `Application` as-is. If you are embedding Circuits elsewhere, instantiate `Application` and inject your own screen to control lifecycle and rendering.
