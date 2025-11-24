#ifndef CIRCUITS_IMAGE_H
#define CIRCUITS_IMAGE_H

#include "core/IWidget.h"

namespace circuits {

    class Image final : public IWidget{
    public:
        explicit Image(const Texture&, const glm::vec2& = {0,0}, const glm::vec2& = {1,1}, const glm::ivec2& = {-1,-1});

        glm::ivec2 onMeasure(const glm::ivec2 &max) override;
        void onDraw(Renderer &) override;
    private:
        Texture m_texture;
        glm::vec2 m_uv_min;
        glm::vec2 m_uv_max;
        glm::ivec2 m_size;
    };

}



#endif //CIRCUITS_IMAGE_H