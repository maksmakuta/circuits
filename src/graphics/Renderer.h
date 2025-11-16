#ifndef CIRCUITS_RENDERER_H
#define CIRCUITS_RENDERER_H

namespace circuits {

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        void load();
        void unload();

        void begin();
        void end();
    };

}

#endif //CIRCUITS_RENDERER_H