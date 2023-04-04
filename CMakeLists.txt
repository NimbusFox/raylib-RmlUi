cmake_minimum_required(VERSION 3.16...3.17)
project(RmlUI_Example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/raylib/src/
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/RmlUi/Include/
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/raylib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/RmlUi)

set(rmlUiFiles
    src/raylibFileInterface.cpp
    src/raylibRmlUi.cpp
    src/raylibRenderInterface.cpp
    src/raylibSystemInterface.cpp
    )

add_executable(RmlUI_Example src/main.cpp ${rmlUiFiles})

target_link_libraries(RmlUI_Example raylib RmlCore RmlDebugger)
