cmake_minimum_required(VERSION 3.10)
project(TicTacTerminal)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source groups for clarity (optional for IDEs)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.h)

# Executable target
add_executable(XO ${SOURCES} ${HEADERS})

# Find SFML (graphics, window, audio)
find_package(SFML 2.5 REQUIRED COMPONENTS audio graphics window)

# Link SFML libraries
target_link_libraries(XO sfml-audio sfml-graphics sfml-window)

# Include directories
target_include_directories(XO PRIVATE src)

# Copy media directory to build output
add_custom_command(TARGET XO POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/media
    $<TARGET_FILE_DIR:XO>/media
)
