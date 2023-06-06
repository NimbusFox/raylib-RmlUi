cmake_minimum_required(VERSION 3.16...3.17)
project(RmlUI_Example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

set(BUILD_SHARED_LIBS ON)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/raylib/src/
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/RmlUi/Include/
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/)

set(CUSTOMIZE_BUILD ON)
set(SUPPORT_FILEFORMAT_TGA ON CACHE INTERNAL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/raylib)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/RmlUi)

set(rmlUiFiles
    src/raylibFileInterface.cpp
    src/raylibRmlUi.cpp
    src/raylibRenderInterface.cpp
    src/raylibSystemInterface.cpp
    src/samples/sample.cpp
    )

set(examples
    RmlUI_Example
    RaylibAnimation_Example
    RaylibBenchmark_Example
    RaylibBitmapfont_Example
    RaylibDatabinding_Example
    )

set(raylibSource
    src/samples/raylib.cpp
    )

set(animationSource
    src/samples/basic/animation.cpp
    src/samples/basic/animationEvent.cpp
    )

set(benchmarkSource
    src/samples/basic/benchmark.cpp
    src/samples/exampleEvent.cpp
    )

set (bitmapfontSource
     src/samples/basic/bitmapfont.cpp
     src/samples/exampleEvent.cpp
     src/samples/basic/bitmapfont/fontEngineBitmap.cpp
     src/samples/basic/bitmapfont/fontEngineInterfaceBitmap.cpp
     )

set (databindingSource
     src/samples/basic/databinding.cpp
     src/samples/exampleEvent.cpp
     src/samples/basic/databinding/basicExample.cpp
     src/samples/basic/databinding/eventsExample.cpp
     src/samples/basic/databinding/invadersExample.cpp
     src/samples/basic/databinding/formsExample.cpp
     )

set(exampleSources
    raylibSource
    animationSource
    benchmarkSource
    bitmapfontSource
    databindingSource
    )

list(LENGTH examples len1)
math(EXPR len2 "${len1} - 1")

foreach(val RANGE ${len2})
    list(GET examples ${val} executable)
    list(GET exampleSources ${val} sources)
    add_executable(${executable} src/main.cpp ${${sources}} ${rmlUiFiles})

    target_link_libraries(${executable} raylib RmlCore RmlDebugger)
endforeach()