cmake_minimum_required(VERSION 3.10)
project(TicTacTerminal)

set(CMAKE_CXX_STANDARD 17)

# Find SFML (now include graphics and window)
find_package(SFML 2.5 COMPONENTS audio graphics window REQUIRED)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Create the executable
add_executable(XO ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(XO sfml-audio sfml-graphics sfml-window)

# Copy media folder (e.g., fonts, sounds, etc.)
file(COPY ${CMAKE_SOURCE_DIR}/src/media DESTINATION ${CMAKE_BINARY_DIR})
