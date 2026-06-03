# This can be any version above the engine version (3.24)
cmake_minimum_required(VERSION 3.24)

project(LazerAssault CXX)

# This can be any version above the engine version (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include the engine module
include(FetchContent)
FetchContent_Declare(
    PotatoEngine
    GIT_REPOSITORY https://github.com/powatos/Potato-Engine.git
    GIT_TAG v1.5.1-alpha
)
FetchContent_MakeAvailable(PotatoEngine)

file(GLOB_RECURSE SOURCES 
    "src/*.h"
    "src/*.hpp"
    "src/*.cpp"
)

# Ensure this matches the path to your main file
add_executable(LazerAssaultGame ${SOURCES})

# Include the src directory for header files
target_include_directories(LazerAssaultGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Link libraries to the game
target_link_libraries(LazerAssaultGame PRIVATE PotatoEngine::PotatoEngine)