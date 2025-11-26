#ifndef CIRCUITS_ICONTEXT_H
#define CIRCUITS_ICONTEXT_H

#include <memory>

#include "IScreen.h"

#include "enums/Cursor.h"
#include "ui/Theme.h"

namespace circuits {

    class IContext {
    public:
        virtual ~IContext() = default;

        virtual void setCursor(Cursor) = 0;

        virtual void go(const std::shared_ptr<IScreen>&) = 0;
        virtual void goBack() = 0;

        virtual glm::ivec2 screenSize() = 0;
    };

}

#endif //CIRCUITS_ICONTEXT_H