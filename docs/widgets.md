# **Widget System Documentation**

This document describes the core widget interface used by the UI framework.
All widgets inherit from `IWidget` and participate in a **measure–layout–draw** pipeline with event handling and update logic.

---

# **Overview**

`IWidget` is an abstract base class that represents a drawable UI element.
It provides:

* Parent–child linkage
* Measurement (desired size)
* Layout (actual geometry)
* Rendering
* Event handling
* State & appearance management
* Modifiers (layout and style hints)

```cpp
class IWidget {
public:
    explicit IWidget(const WidgetPtr& parent = nullptr);
    virtual ~IWidget() = default;

    virtual glm::ivec2 onMeasure(const glm::ivec2& max) = 0;
    virtual void onLayout(const Rect& r);
    virtual void onDraw(Renderer&) = 0;
    virtual void onUpdate(float dt);

    virtual void onEvent(const Event& e);

    void setModifier(const Modifier&);
    void setRect(const Rect&);
    void setState(State);
    void setAppearance(Appearance);
    void setParent(const WidgetPtr&);

    [[nodiscard]] Modifier  getModifier() const;
    [[nodiscard]] Rect      getRect() const;
    [[nodiscard]] State     state() const;
    [[nodiscard]] Appearance getAppearance() const;
    [[nodiscard]] WidgetPtr getParent() const;

private:
    Rect m_rect;
    std::weak_ptr<IWidget> m_parent;
    Modifier m_modifier;
    State m_state = State::Normal;
    Appearance m_appearance = Appearance::Normal;
};
```

---

# **Widget Lifecycle**

Each widget goes through a predictable lifecycle:

```
[Measure] → [Layout] → [Draw] → [Update] → [Events]
```

## **1. Measurement — `onMeasure(max)`**

Every widget must implement:

```cpp
glm::ivec2 onMeasure(const glm::ivec2& max)
```

This method determines the **desired size** of the widget given the parent-imposed maximum.

Typical implementations:

* Text widget returns (textWidth, textHeight)
* Container widget iterates children and computes layout size
* Image widget returns (imageWidth, imageHeight)

**Output:**
A size **not larger** than `max`.

---

## **2. Layout — `onLayout(rect)`**

Called after measurement.
This is where the widget receives its **final geometry**.

Default behavior:

```cpp
virtual void onLayout(const Rect& r) {
    setRect(r);
}
```

Override only if your widget lays out children (containers like `Row`, `Column`, etc.)

---

## **3. Drawing — `onDraw(renderer)`**

Each widget must implement drawing using the shared `Renderer`.

```cpp
virtual void onDraw(Renderer& r) = 0;
```

Common tasks:

* Draw backgrounds
* Draw borders
* Draw text
* Draw child widgets (container widgets)

Example (pseudo):

```cpp
const auto rect = getRect();
r.rect(rect.pos, rect.size);
r.fill(color/texture);
// and/or
r.stroke(color, thickness)
```

---

## **4. Updating — `onUpdate(dt)`**

Called every frame (optional).

Used for:

* Animations
* Timers
* Hover transitions
* State machines

Base implementation does nothing.

---

## **5. Event Handling — `onEvent(e)`**

Override to react to input:

* Mouse movement
* Mouse press/release
* Keyboard
* Focus
* App-level events

Example:

```cpp
void Button::onEvent(const Event& e) override {
    if (e.type == MouseDown && getRect().contains(e.position)) {
        setState(State::Pressed);
    }
}
```

---

# **State & Appearance**

Every widget stores two concepts:

### **State**

A runtime interaction flag:

* `State::Normal`
* `State::Hover`
* `State::Active`
* `State::Disable`

Used by rendering logic to pick colors, shadows, animations.

---

### **Appearance**

Static visual mode:

 * `Appearance::Normal`
 * `Appearance::Surface`
 * `Appearance::SurfaceVariant`
 * `Appearance::Primary`
 * `Appearance::Secondary`
 * `Appearance::Error`
 
Used for rendering text with good contrast

---

# **Modifiers**

Modifiers control layout and positional behavior.

```cpp
void setModifier(const Modifier& m);
Modifier getModifier() const;
```

Typical fields in `Modifier`:

* width/height policy (filled, percentage from parent, or based on content size)
* margins / padding
* gravity

Modifiers influence **onMeasure** and **onLayout** in parent widgets.

---

# **Geometry Access**

Each widget stores its bounding rectangle:

```cpp
Rect getRect() const;
void setRect(const Rect&);
```

Used for:

* Drawing
* Hit-testing
* Event routing

Rect contains:

```cpp
 struct Rect final {
        Rect();
        Rect(const glm::ivec2& p, const glm::ivec2& s);

        static Rect fromPoints(const glm::ivec2& p0, const glm::ivec2& p1);

        [[nodiscard]] bool contains(const glm::ivec2& p) const;

        glm::ivec2 pos{0};
        glm::ivec2 size{0};
    };
```

---

# **Parenting**

Every widget may have a parent.

```cpp
void setParent(const WidgetPtr&);
WidgetPtr getParent() const;
```

Useful for:

* Event bubbling
* Layout propagation
* Theme inheritance
* Relative positioning

The parent is stored as a `weak_ptr` to avoid cycles.  
But in current implementation it's not used....

---

# **WidgetPtr and WidgetList**

Convenience aliases:

```cpp
using WidgetPtr  = std::shared_ptr<IWidget>;
using WidgetList = std::initializer_list<WidgetPtr>;
```

Allows container constructors like:

```cpp
column({
    label("Hello"),
    button("OK"),
    button("Cancel")
});
```

---

# **How to Implement a Widget**

A minimal example:

```cpp
class Spacer : public IWidget {
public:
    Spacer(const WidgetPtr& parent = nullptr)
        : IWidget(parent) {}

    glm::ivec2 onMeasure(const glm::ivec2& max) override {
        return glm::ivec2(1, 1); // minimum
    }

    void onDraw(Renderer& r) override {
        // nothing
    }
};
```

A more realistic button:

See [Button.h](../src/ui/widget/Button.h) and [Button.cpp](../src/ui/widget/Button.cpp)

---

# **Container Widgets**

If you build widgets like `Row`, `Column`, `Stack`, etc., they will:

* Measure children inside `onMeasure`
* Lay out children in `onLayout`
* Call children’s `onDraw` inside `onDraw`

Useful examples [here](../src/ui/layout)

---

# **Event Propagation Model**

Widgets typically receive events in this order:

```
Root → Containers → Leaf widgets
```

Common strategies:

* **First-hit**: send event only to the widget under cursor
* **Capture**: widget can claim exclusive handling
* **Bubble up**: if not handled, pass to parent

---

# **Summary**

`IWidget` provides all primitives needed to build a UI framework:

✔ Measurement  
✔ Layout  
✔ Rendering  
✔ Updating  
✔ Event handling  
✔ State and appearance  
✔ Parent–child hierarchy  
✔ Modifier-based layout control  

With this, you can build higher-level widgets (buttons, lists, text fields) and containers (rows, columns, stacks) in a structured and predictable way.
