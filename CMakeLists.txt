CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)
PROJECT(minesweeper C)

# Application version
SET(MINESWEEPER_AUTHOR "Thibault Meyer")
SET(MINESWEEPER_APPNAME "Minesweeper")
SET(MINESWEEPER_VERSION "1.0")
SET(MINESWEEPER_VERSION_WIN_FILE "1,0,0,0")
SET(MINESWEEPER_COPYRIGHT "© 2020 ${MINESWEEPER_AUTHOR}")

# Settings
SET(CMAKE_C_STANDARD 99)
SET(CMAKE_C_FLAGS "-Wall")
SET(CMAKE_CXX_FLAGS_DEBUG "-g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Configure version.h file
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/res/version.h.template ${CMAKE_SOURCE_DIR}/src/version.h)

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

# Defines properties for MacOS app bundle
IF (APPLE)
    SET(MACOSX_BUNDLE_LONG_VERSION_STRING ${MINESWEEPER_VERSION})
    SET(MACOSX_BUNDLE_SHORT_VERSION_STRING ${MINESWEEPER_VERSION})
    SET(MACOSX_BUNDLE_COPYRIGHT ${MINESWEEPER_COPYRIGHT})
    SET(MACOSX_BUNDLE_BUNDLE_NAME ${MINESWEEPER_APPNAME})
    SET(MAC_ICON ${CMAKE_SOURCE_DIR}/res/application-icon-macos.icns)
    SET_SOURCE_FILES_PROPERTIES(${MAC_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    SET(MACOSX_BUNDLE_ICON_FILE application-icon-macos.icns)
ENDIF (APPLE)

# Files
ADD_EXECUTABLE(
        minesweeper WIN32
        MACOSX_BUNDLE
        src/gui/gui.h
        src/gui/gui_game_callback_cell_update.c
        src/gui/gui_image_load_from_memory_scale.c
        src/gui/gui_main_callback_app_activate.c
        src/gui/gui_main_callback_click_mine.c
        src/gui/gui_main_callback_menu_about.c
        src/gui/gui_main_callback_menu_new_game.c
        src/gui/gui_main_callback_window_destroy.c
        src/gui/gui_main_initialize_main_window.c
        src/gui/gui_toolbox_is_gtk_dark_theme_enabled.c
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
        src/main.c
        minesweeper.rc
        ${MAC_ICON})

# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(minesweeper -lm ${GTK3_LIBRARIES})

# Install
INSTALL(TARGETS minesweeper DESTINATION bin)
