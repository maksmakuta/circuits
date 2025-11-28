#include "IWidget.h"

namespace circuits {


    void IWidget::setModifier(const Modifier& m) {
        m_modifier = m;
    }

    void IWidget::setRect(const Rect& r) {
        m_rect = r;
    }

    void IWidget::setState(const State s) {
        if (m_state == s) return;
        m_state = s;
    }

    void IWidget::setAppearance(const Appearance a) {
        m_appearance = a;
    }

    void IWidget::setParent(const WidgetPtr& p) {
        m_parent = p;
    }

    void IWidget::recompose() {
        pushEvent(Event::Recompose());
    }

    Modifier IWidget::getModifier() const {
        return m_modifier;
    }

    Rect IWidget::getRect() const {
        return m_rect;
    }

    State IWidget::state() const {
        return m_state;
    }

    Appearance IWidget::getAppearance() const {
        return m_appearance;
    }

    WidgetPtr IWidget::getParent() const {
        return m_parent.lock();
    }

}