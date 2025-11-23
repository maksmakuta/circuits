#include "UI.h"

#include "theme/ThemeManager.h"

namespace circuits {

    WidgetPtr Label(std::string text, Modifier mod){
        return nullptr;
    }

    WidgetPtr Button(WidgetPtr inner, Modifier mod){
        return nullptr;
    }

    WidgetPtr Button(std::string text, Modifier mod){
        return nullptr;
    }

    WidgetPtr Input(std::string text, Modifier mod){
        return nullptr;
    }

    WidgetPtr Switch(bool state, Modifier mod){
        return nullptr;
    }

    WidgetPtr Image(Texture& tex, Modifier mod){
        return nullptr;
    }

    WidgetPtr Card(WidgetPtr inner, Modifier mod){
        return nullptr;
    }

    WidgetPtr Tooltip(WidgetPtr inner, Modifier mod){
        return nullptr;
    }

    WidgetPtr Notification(std::string message, Modifier mod){
        return nullptr;
    }

    WidgetPtr column(const WidgetList& list, Modifier mod){
        return nullptr;
    }

    WidgetPtr row(const WidgetList& list, Modifier mod){
        return nullptr;
    }

    WidgetPtr grid(const WidgetList& list, Modifier mod){
        return nullptr;
    }

    WidgetPtr box(const WidgetList& list, Modifier mod){
        return nullptr;
    }

}
