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

add_executable(circuits
        src/base/interface/IScreen.cpp
        src/base/interface/IScreen.h

        src/components/Gate.cpp
        src/components/Gate.h
        src/components/Toggle.cpp
        src/components/Toggle.h
        src/components/Bulb.cpp
        src/components/Bulb.h
        src/components/Switch.cpp
        src/components/Switch.h
        src/components/Clock.cpp
        src/components/Clock.h
        src/components/Display.cpp
        src/components/Display.h
        src/components/Constant.cpp
        src/components/Constant.h

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

        src/simulator/Application.cpp
        src/simulator/Application.h
        src/simulator/screen/MainScreen.cpp
        src/simulator/screen/MainScreen.h
        src/simulator/screen/MainVM.cpp
        src/simulator/screen/MainVM.h

        src/utils/Assets.cpp
        src/utils/Assets.h

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
)
