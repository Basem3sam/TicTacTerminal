cmake_minimum_required(VERSION 3.10)
project(TicTacTerminal)

set(CMAKE_CXX_STANDARD 17)

# Find SFML package (make sure SFML is installed)
find_package(SFML 2.5 COMPONENTS audio REQUIRED)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h") # Optional

# Create the executable (this name must match below)
add_executable(XO ${SOURCES} ${HEADERS})

# Link SFML to the correct target (XO)
target_link_libraries(XO sfml-audio)

# CMakeLists.txt
file(COPY ${CMAKE_SOURCE_DIR}/src/media DESTINATION ${CMAKE_BINARY_DIR})
