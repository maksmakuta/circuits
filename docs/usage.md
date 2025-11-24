# Quickstart

Follow these steps to build and run Circuits, then plug in your own UI.

## Prerequisites
- CMake 4.0+ and a C++20 compiler.
- Development packages for SDL3, OpenGL 4.6, GLM, and Freetype (resolved via `find_package`).
- Bundled dependencies (GLAD, LodePNG, OpenSans) are already included.

## Build
```sh
cmake -S . -B build
cmake --build build
```
This produces the `build/circuits` executable.

## Run
```sh
./build/circuits
```
`Application::run()` sets up the window, renderer, theme, and the active screen before entering the frame loop.

## Create your own screen
1. Derive from `circuits::IScreen` and implement the lifecycle methods.
2. Build a widget tree (see [Building UIs with widgets](ui-toolkit.md)) and store it on your screen.
3. Wire input to your widgets inside `onEvent` and update them in `onUpdate`.
4. Draw the tree in `onDraw(Renderer&)`.
5. In `Application::Application()`, replace `MainScreen` with your screen to make it the default view.

## Embed Circuits
If you prefer to keep your own `main`, link against the Circuits targets and construct `circuits::Application` yourself. Provide your screen instance and let `run()` manage windowing and rendering for you.
