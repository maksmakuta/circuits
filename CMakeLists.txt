cmake_minimum_required(VERSION 4.0)
project(circuits)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)

add_subdirectory(libs/glad)
add_subdirectory(libs/LodePNG)
add_subdirectory(libs/OpenSans_ettf)

add_executable(circuits

        src/core/IContext.h
        src/core/IScreen.h
        src/core/IViewmodel.h
        src/core/IWidget.cpp
        src/core/IWidget.h
        src/core/Modifier.cpp
        src/core/Modifier.h
        src/core/Rect.cpp
        src/core/Rect.h
        src/core/UIScreen.cpp
        src/core/UIScreen.h

        src/enums/Appearance.h
        src/enums/Cap.h
        src/enums/Cursor.h
        src/enums/FontRole.h
        src/enums/Gravity.h
        src/enums/HAlign.h
        src/enums/Joint.h
        src/enums/SizeUnit.h
        src/enums/State.h
        src/enums/ThemeName.h
        src/enums/VAlign.h

        src/graphics/Renderer.cpp
        src/graphics/Renderer.h
        src/graphics/Color.cpp
        src/graphics/Color.h
        src/graphics/Font.cpp
        src/graphics/Font.h
        src/graphics/Texture.cpp
        src/graphics/Texture.h
        src/graphics/Vertex.cpp
        src/graphics/Vertex.h
        src/graphics/Shader.cpp
        src/graphics/Shader.h
        src/graphics/Path.cpp
        src/graphics/Path.h

        src/rx/Observable.h

        src/simulator/screen/MainScreen.cpp
        src/simulator/screen/MainScreen.h
        src/simulator/screen/MainVM.cpp
        src/simulator/screen/MainVM.h
        src/simulator/Application.cpp
        src/simulator/Application.h

        src/ui/layout/Column.cpp
        src/ui/layout/Column.h
        src/ui/layout/Row.cpp
        src/ui/layout/Row.h

        src/ui/widget/Button.cpp
        src/ui/widget/Button.h
        src/ui/widget/Card.cpp
        src/ui/widget/Card.h
        src/ui/widget/Checkbox.cpp
        src/ui/widget/Checkbox.h
        src/ui/widget/Image.cpp
        src/ui/widget/Image.h
        src/ui/widget/Input.cpp
        src/ui/widget/Input.h
        src/ui/widget/Label.cpp
        src/ui/widget/Label.h
        src/ui/widget/Toggle.cpp
        src/ui/widget/Toggle.h

        src/ui/Theme.cpp
        src/ui/Theme.h
        src/ui/UI.cpp
        src/ui/UI.h

        src/utils/ColorUtils.cpp
        src/utils/ColorUtils.h

        src/window/Event.cpp
        src/window/Event.h
        src/window/Window.cpp
        src/window/Window.h

        src/main.cpp
)

target_include_directories(circuits PUBLIC src)
target_link_libraries(circuits PRIVATE
        SDL3::SDL3
        glm::glm
        OpenGL::GL
        glad::glad
        LodePNG
        Freetype::Freetype
        open_sans_data
)
