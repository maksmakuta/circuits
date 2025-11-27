# Rendering

 Circuits uses own rendering abstraction based on OpenGL library called Renderer.  
 You can check Renderer API [here](../src/graphics/Renderer.h)  
 The `Renderer` class provides a high-level API for drawing shapes, text, paths, and textures.  
 It is designed to be used inside a UI rendering loop and supports transformations, stroke/fill operations, and vector paths.  

---

## Table of Contents

* [Initialization](#initialization)
* [Frame Rendering Workflow](#frame-rendering-workflow)
* [Resizing](#resizing)
* [Transformations](#transformations)
* [Path Drawing API](#path-drawing-api)
* [Primitive Drawing](#primitive-drawing)
* [Text Rendering](#text-rendering)
* [Fill and Stroke](#fill-and-stroke)
* [State Settings](#state-settings)
* [Complete Example](#complete-example)

---

# Initialization

Before rendering anything, the renderer must be created and loaded.

```cpp
Renderer renderer;

renderer.load();   // Initialize GPU resources
```

When shutting down:

```cpp
renderer.unload();
```

The destructor also cleans up resources, but calling `unload()` explicitly is recommended.

---

# Frame Rendering Workflow

Each frame must follow this call order:

```cpp
renderer.begin();

// draw...
renderer.rect(...);
renderer.text(...);

renderer.flush(); // (optional) manually send batches

renderer.end();
```

### **begin()**

Starts a new frame, clears internal state.

### **flush()**

Sends all currently batched draw commands to the GPU.
Usually you don’t need to call it manually.

### **end()**

Finalizes the frame.

---

# Resizing

Call this whenever the window or framebuffer is resized:

```cpp
renderer.resize({width, height});
```

This updates internal projection matrices.

---

# Transformations

These functions affect subsequent drawing commands:

```cpp
renderer.translate({x, y});
renderer.scale(2.0f);
renderer.scale({sx, sy});
renderer.rotate(angleRadians);
renderer.rotate(angleRadians, pivotPoint);
```

Transformations stack and are applied in order.

---

# Path Drawing API

Paths allow you to create complex vector shapes.

# Primitive Drawing

These helpers draw shapes without manually creating paths.

### Points and Lines

```cpp
renderer.point({x, y});
renderer.line({x1, y1}, {x2, y2});
```

### Triangles

```cpp
renderer.triangle(p1, p2, p3);
```

### Rectangles

Several overloads:

```cpp
renderer.rect(pos, size);                    // simple
renderer.rect(pos, size, radius);            // uniform rounded corners
renderer.rect(pos, size, {rx, ry});          // elliptical corners
renderer.rect(pos, size, {r1, r2, r3, r4});  // each corner
```

### Circle / Ellipse

```cpp
renderer.circle(center, radius);
renderer.ellipse(center, {rx, ry});
```

### Arc / Pie

```cpp
renderer.arc(center, {rx, ry}, startAngle, endAngle);
renderer.pie(center, {rx, ry}, startAngle, endAngle); // filled sector
```
---

### Start a new custom path

```cpp
renderer.newPath();
renderer.moveTo({x1, y1});
renderer.lineTo({x2, y2});
renderer.quadTo(control, end);
renderer.cubicTo(c1, c2, end);
renderer.arcTo(center, radiusVec, startAngle, endAngle, ccw);
renderer.close();
```

After the path is complete, it can be:

### Filled

```cpp
renderer.fill(Color(0xFF00FF00));
```

### Stroked

```cpp
renderer.stroke(Color(0xFFFF0000), 2.0f);
```

### Or drawn from a reusable `Path` object

```cpp
Path p = ...;
renderer.path(p);
```

### So to render a filled rectangle you'll need to write:

```cpp
 renderer.rect({pos_x,pos_y},{size_w, size_h});
 renderer.fill(Color(0xFF00FF00));
```

First path, then draw style

---

# Text Rendering

```cpp
renderer.text(font, "Hello!", {x, y}, Color(0xFFFFFFFF));
```

Text alignment depends on:

* `setAlign(HAlign)`
* `setBaseline(VAlign)`

For example:

```cpp
renderer.setAlign(HAlign::Center);
renderer.setBaseline(VAlign::Middle);
renderer.text(font, "Centered", {200, 200});
```

---

# Fill and Stroke

### Fill With Color

```cpp
renderer.fill(Color(0xFF0000FF)); // red
```

### Fill With Texture

```cpp
renderer.fill(texture, uvStart, uvEnd);
```

### Stroke

```cpp
renderer.stroke(Color::Black, 1.5f);
```

Stroke follows the most recent path or primitive.

---

# State Settings

These functions control rendering behavior:

```cpp
renderer.setCap(Cap::Round);
renderer.setJoint(Joint::Miter);
renderer.setAlign(HAlign::Left);
renderer.setBaseline(VAlign::Top);
```

* **Cap** controls how stroke ends look.
* **Joint** controls how corners connect.
* **Align** controls text horizontal alignment.
* **Baseline** controls text vertical alignment.

---

# Complete Example

```cpp
Renderer r;
r.load();
r.resize({800, 600});

while (running) {
    r.begin();

    r.setAlign(HAlign::Center);
    r.setBaseline(VAlign::Middle);

    r.text(font, "Hello Renderer!", {400, 300});

    r.rect({100, 100}, {200, 120}, 12.0f);
    r.fill(Color(0x00FF88FF));

    r.line({50,50}, {200,200});

    r.end();
}

r.unload();
```
 