# Rendering with `Renderer`

`circuits::Renderer` exposes immediate-mode primitives that you can call from widgets or screens during `onDraw`.

## Frame flow
`Application` prepares the frame with `Renderer::begin()` and `Renderer::end()`; your code should only issue drawing commands between those calls (typically inside `IScreen::onDraw`). If the window resizes, `Renderer::resize()` is called automatically.

## Drawing text
```cpp
void MyScreen::onDraw(Renderer& r) {
    r.setBaseline(Baseline::Top);
    r.text(currentTheme().font, "Hello, Circuits!", {16.f, 16.f});
}
```

## Drawing shapes
- `rect(pos, size)` draws an axis-aligned rectangle; overloads accept radii for rounded corners.
- `circle(center, radius)` and `ellipse(center, radii)` cover basic geometry.
- `line(a, b)` renders a stroked line; call `stroke(color, thickness)` after defining a path.
- `fill(Color)` sets the fill paint for subsequent path operations.

Example: a filled card with an outline:
```cpp
r.fill(Color(0xFF202020));
r.rect({32, 32}, {320, 200}, 12.f);
r.stroke(Color(0xFF808080), 2.f);
```

## Working with textures
If you load a `Texture`, you can blit it with:
```cpp
r.fill(texture, /*uv0*/{0,0}, /*uv1*/{1,1});
r.rect({64, 64}, {128, 128});
```

## Paths and transforms
For custom shapes, build a path with `newPath()`, `moveTo`, `lineTo`, `quadTo`, `cubicTo`, or `arcTo`, then call `path()` with your constructed `Path`. Use `translate`, `scale`, or `rotate` to position drawings without recomputing coordinates.
