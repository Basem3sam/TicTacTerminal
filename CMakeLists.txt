cmake_minimum_required(VERSION 3.10)
project(TicTacTerminal)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to enable/disable SFML GUI
option(ENABLE_SFML_GUI "Enable SFML GUI support" ON)

# Gather source and header files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.h)

# Create executable
add_executable(XO ${SOURCES} ${HEADERS})

# Include project source directory
target_include_directories(XO PRIVATE src)

# ---- SFML GUI Support ----
if(ENABLE_SFML_GUI)
  find_package(SFML 2.5 COMPONENTS audio graphics window QUIET)

  if(SFML_FOUND)
    message(STATUS "Found SFML ${SFML_VERSION}, enabling GUI support")

    # Check for minimum version
    if(SFML_VERSION VERSION_LESS "2.5")
      message(FATAL_ERROR "SFML version must be at least 2.5! Found ${SFML_VERSION}")
    endif()

    # Enable GUI code in source
    target_compile_definitions(XO PRIVATE ENABLE_SFML_GUI)

    # Link SFML
    target_link_libraries(XO PRIVATE sfml-audio sfml-graphics sfml-window)
  else()
    message(WARNING "SFML not found. Building terminal-only version (GUI disabled).")
  endif()
endif()

# ---- Copy media directory to output ----
if(EXISTS "${CMAKE_SOURCE_DIR}/src/media")
  add_custom_command(TARGET XO POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/src/media"
    "$<TARGET_FILE_DIR:XO>/media"
  )
endif()
