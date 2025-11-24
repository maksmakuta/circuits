# Running or embedding the simulator

The repository ships a ready-to-run simulator binary that exercises the UI stack. You can run it directly or swap in your own screen to prototype features.

## Running the provided binary
After building (see [Quickstart](usage.md)), launch:
```sh
./build/circuits
```

The simulator will open a window, load the current theme, and render the active screen.

## Replacing the startup screen
To show your own UI first:
1. Implement `IScreen` (e.g., `MyScreen`) with the lifecycle methods.
2. In `src/simulator/Application.cpp`, replace `MainScreen` with your screen inside the `Application` constructor:
   ```cpp
   Application::Application() {
       m_screen = std::make_unique<MyScreen>();
   }
   ```
3. Rebuild and re-run. `Application::run()` handles the rest of the loop (events → update → draw → swap).

## Embedding in another project
If you want to reuse Circuits inside another executable, link against the library targets and construct `circuits::Application` from your own `main()`. Provide your custom screen to drive the visuals and reuse the built-in renderer and windowing stack.
