#include "Application.h"

#include <iostream>
#include <SDL3/SDL_events.h>

#include "graphics/Renderer.h"

namespace circuits {

    Application::Application() {
    }

    void Application::pollEvents() {

    }

    void Application::updateDelta() {
    }

    int Application::run() {
        m_window.swap();
        while (!m_window.isClosed()) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_EVENT_QUIT:
                        m_window.close();
                        break;
                    case SDL_EVENT_TEXT_INPUT:
                        m_text.append(event.text.text);
                        std::cout << m_text << std::endl;
                        break;
                    case SDL_EVENT_TEXT_EDITING:

                        break;
                    case SDL_EVENT_KEY_DOWN:
                        switch (event.key.key) {
                        case SDLK_BACKSPACE:
                                if (!m_text.empty())
                                    m_text.pop_back();
                                break;
                            case SDLK_ESCAPE:
                                m_text_input = !m_text_input;
                                m_window.enableInput(m_text_input);
                            case SDLK_1:
                                m_window.setCursor(Cursor::Default);
                                break;
                            case SDLK_2:
                                m_window.setCursor(Cursor::Hand);
                                break;
                            case SDLK_3:
                                m_window.setCursor(Cursor::Text);
                                break;
                            case SDLK_4:
                                m_window.setCursor(Cursor::ResizeH);
                                break;
                            case SDLK_5:
                                m_window.setCursor(Cursor::ResizeV);
                                break;
                            case SDLK_6:
                                m_window.setCursor(Cursor::Move);
                                break;
                            case SDLK_7:
                                m_window.setCursor(Cursor::No);
                                break;
                            case SDLK_8:
                                m_window.setCursor(Cursor::Wait);
                                break;

                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }

            clear(0xFF00FF00);
            m_window.swap();
        }
        return 0;
    }

}
