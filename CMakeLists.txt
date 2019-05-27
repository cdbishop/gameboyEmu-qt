project(gameboyEmu)
cmake_minimum_required(VERSION 2.8.12)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5UiTools REQUIRED)

file(GLOB_RECURSE source_list RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE headers_list RELATIVE ${CMAKE_SOURCE_DIR} "src/*.hpp")
file(GLOB_RECURSE txt_list RELATIVE ${CMAKE_SOURCE_DIR} "src/*.txt")
file(GLOB_RECURSE ui_headers_list RELATIVE ${CMAKE_SOURCE_DIR} "src/**/ui_*.h")

message(STATUS "ui_headers_list = ${ui_headers_list}")

file(GLOB_RECURSE roms_list RELATIVE ${CMAKE_SOURCE_DIR} "roms/*.gb")
file(GLOB_RECURSE ui_list RELATIVE ${CMAKE_SOURCE_DIR} "ui/*.ui")

file(MAKE_DIRECTORY "bin/roms")
file(MAKE_DIRECTORY "bin/ui")

foreach(rom IN LISTS roms_list)
    get_filename_component(source_path "${rom}" NAME)    
    configure_file("${rom}" "bin/roms/${source_path}" COPYONLY)
endforeach()

foreach(ui IN LISTS ui_list)
    get_filename_component(source_path "${ui}" NAME)    
    configure_file("${ui}" "bin/ui/${source_path}" COPYONLY)
endforeach()

foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

foreach(source IN LISTS headers_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

foreach(source IN LISTS ui_headers_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

foreach(source IN LISTS txt_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

add_executable(${PROJECT_NAME} ${source_list} ${headers_list} ${txt_list} ${ui_headers_list})
target_include_directories(${PROJECT_NAME} PRIVATE "src")
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::UiTools)

set_property(TARGET gameboyEmu PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")