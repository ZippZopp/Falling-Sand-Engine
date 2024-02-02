cmake_minimum_required(VERSION 3.22)
project(simpleworld)

set(CMAKE_CXX_STANDARD 17)

# Define the executable
add_executable(simpleworld main.cpp Renderer/Renderer.h Renderer/Renderer.cpp Renderer/Renderer.cpp SimpleWorld/SimpleWorld.cpp SimpleWorld/SimpleWorld.h  Elements/Interfaces/Element.h Elements/Interfaces/Element.h ProjectConstants.h 2dWorld/TwoDEnvironment.h 2dWorld/TwoDEnvironment.cpp)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Include the SDL2 header files
include_directories(${SDL2_INCLUDE_DIRS})

# Link against the SDL2 libraries for the "simpleworld" target
target_link_libraries(simpleworld ${SDL2_LIBRARIES})

