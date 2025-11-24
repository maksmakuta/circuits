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
        src/core/IScreen.h
        src/core/IViewmodel.h
        src/core/IWidget.h
        src/core/Modifier.cpp
        src/core/Modifier.h
        src/core/Rect.cpp
        src/core/Rect.h

        src/enums/Align.h
        src/enums/Baseline.h
        src/enums/Cap.h
        src/enums/Gravity.h
        src/enums/Joint.h
        src/enums/SizeUnit.h
        src/enums/SystemTheme.h

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

        src/simulator/screen/MainScreen.cpp
        src/simulator/screen/MainScreen.h
        src/simulator/screen/MainVM.cpp
        src/simulator/screen/MainVM.h
        src/simulator/Application.cpp
        src/simulator/Application.h

        src/ui/theme/Theme.cpp
        src/ui/theme/Theme.h
        src/ui/theme/ThemeManager.cpp
        src/ui/theme/ThemeManager.h
        src/ui/widget/Label.cpp
        src/ui/widget/Label.h
        src/ui/UI.cpp
        src/ui/UI.h

        src/window/Event.cpp
        src/window/Event.h
        src/window/Window.cpp
        src/window/Window.h

        src/main.cpp
        src/enums/State.h
        src/ui/layout/Column.cpp
        src/ui/layout/Column.h
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
