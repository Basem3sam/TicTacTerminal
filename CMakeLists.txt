cmake_minimum_required(VERSION 3.10)
project(TicTacTirminal)

set(CMAKE_CXX_STANDARD 17)

# Collect all source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

# Collect all headers (optional, for IDEs)
file(GLOB_RECURSE HEADERS
    "src/*.h"
)

# Create the executable
add_executable(XO ${SOURCES} ${HEADERS})
