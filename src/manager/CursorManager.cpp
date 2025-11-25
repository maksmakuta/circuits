#include "CursorManager.h"

#include <ranges>
#include <unordered_map>
#include <SDL3/SDL_mouse.h>

namespace circuits {
    class CursorManager {
    public:
        static CursorManager& instance() {
            static CursorManager instance;
            return instance;
        }

        void setCursor(Cursor type) {
            if (type != currentType) {
                SDL_SetCursor(cursors[type]);
                currentType = type;
            }
        }

        Cursor getCurrent() const {
            return currentType;
        }

    private:
        std::unordered_map<Cursor, SDL_Cursor*> cursors;
        Cursor currentType;

        CursorManager() {
            cursors[Cursor::Default]     = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            cursors[Cursor::IBeam]       = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_TEXT);
            cursors[Cursor::Hand]        = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
            cursors[Cursor::ResizeV]     = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NS_RESIZE);
            cursors[Cursor::ResizeH]     = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_EW_RESIZE);

            currentType = Cursor::Default;
            SDL_SetCursor(cursors[currentType]);
            SDL_ShowCursor();
        }

        ~CursorManager() {
            for (const auto &cursor: cursors | std::views::values) {
                SDL_DestroyCursor(cursor);
            }
        }
    };

    void setCursor(const Cursor &cursor) {
        CursorManager::instance().setCursor(cursor);
    }

}
