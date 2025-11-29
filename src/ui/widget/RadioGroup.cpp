#include "RadioGroup.h"

#include "ui/layout/Row.h"

namespace circuits {

    RadioGroup::RadioGroup(Observable<int>& s,const WidgetList& widgets): RadioGroup(s.getValue(), widgets) {
        s.observe([this](const int& value) {
            select(value);
        });
    }

    RadioGroup::RadioGroup(const int s,const WidgetList& widgets): Column(widgets), m_selected(s) {
        for (const auto& widget : widgets) {
            if (const auto row = std::dynamic_pointer_cast<Row>(widget)) {

            }
        }
    }

    void RadioGroup::select(const int n) {
        if (m_selected != n) {
            m_selected = n;
            for (const auto& [id, ptr] : m_table) {
                ptr->select(id == n);
            }
        }
    }

    int RadioGroup::selected() const {
        return m_selected;
    }

}
