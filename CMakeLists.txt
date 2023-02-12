cmake_minimum_required(VERSION 3.24)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v3.0.0
        )

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
# ------------------------------------------------------------------------------

project(StackArrayTUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(StackArrayTUI main.cpp scroller.cpp scroller.hpp)

target_link_libraries(StackArrayTUI
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component # Not needed for this example.
        )
