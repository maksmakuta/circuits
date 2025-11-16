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
        src/base/IScreen.cpp
        src/base/IScreen.h
        src/base/IWidget.cpp
        src/base/IWidget.h

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

        src/simulator/Application.cpp
        src/simulator/Application.h
        src/simulator/screen/MainScreen.cpp
        src/simulator/screen/MainScreen.h

        src/ui/layout/Column.cpp
        src/ui/layout/Column.h
        src/ui/layout/Row.cpp
        src/ui/layout/Row.h
        src/ui/widget/Button.cpp
        src/ui/widget/Button.h
        src/ui/widget/Label.cpp
        src/ui/widget/Label.h
        src/ui/widget/Input.cpp
        src/ui/widget/Input.h
        src/ui/widget/Progress.cpp
        src/ui/widget/Progress.h
        src/ui/widget/Divider.cpp
        src/ui/widget/Divider.h
        src/ui/widget/Image.cpp
        src/ui/widget/Image.h
        src/ui/Modifier.cpp
        src/ui/Modifier.h
        src/ui/Theme.cpp
        src/ui/Theme.h

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
