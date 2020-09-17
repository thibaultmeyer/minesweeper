CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)
PROJECT(minesweeper C)

# Settings
SET(CMAKE_C_STANDARD 99)
SET(CMAKE_C_FLAGS "-Wall")
SET(CMAKE_CXX_FLAGS_DEBUG "-g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Configure windres: don't use flags
IF (MINGW)
    SET(CMAKE_RC_COMPILER_INIT windres)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILE_OBJECT
            "<CMAKE_RC_COMPILER> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
ENDIF (MINGW)

# Display build type
IF (NOT CMAKE_BUILD_TYPE)
    MESSAGE(STATUS "Build type: -")
ELSE (NOT CMAKE_BUILD_TYPE)
    MESSAGE(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
ENDIF (NOT CMAKE_BUILD_TYPE)

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

# Files
ADD_EXECUTABLE(
        minesweeper WIN32
        src/main.c
        src/minesweeper/minesweeper.h
        src/minesweeper/minesweeper_create.c
        src/minesweeper/minesweeper_destroy.c
        src/minesweeper/minesweeper_dump.c
        src/minesweeper/minesweeper_get_adjacent_cells.c
        src/minesweeper/minesweeper_get_cell.c
        src/minesweeper/minesweeper_is_all_cells_open.c
        src/minesweeper/minesweeper_open_cell.c
        src/minesweeper/minesweeper_toggle_flag.c
        src/version.h
        minesweeper.rc)

# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(minesweeper -lm ${GTK3_LIBRARIES})

# Install
INSTALL(TARGETS minesweeper DESTINATION bin)
