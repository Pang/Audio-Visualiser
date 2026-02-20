cmake_minimum_required(VERSION 3.20)
project(AudioVisualizer)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML CONFIG REQUIRED COMPONENTS
    Graphics
    Window
    Audio
    System
)

find_package(FFTW3 CONFIG REQUIRED)

add_executable(AudioVisualizer src/main.cpp)

target_link_libraries(AudioVisualizer PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::Audio
    SFML::System
    FFTW3::fftw3
)