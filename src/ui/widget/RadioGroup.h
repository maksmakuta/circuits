#ifndef CIRCUITS_RADIOGROUP_H
#define CIRCUITS_RADIOGROUP_H

#include "RadioButton.h"
#include "rx/Observable.h"
#include "ui/layout/Column.h"

namespace circuits {

    class RadioGroup final : public Column {
    public:
        RadioGroup(Observable<int>& s,const WidgetList& widgets);
        RadioGroup(int s,const WidgetList& widgets);

        void select(int n);
        int selected() const;

    private:
        int m_selected;
        std::unordered_map<int, RadioButton*> m_table;
    };

}

#endif //CIRCUITS_RADIOGROUP_H