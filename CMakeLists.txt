cmake_minimum_required(VERSION 3.16)

project(RFOS VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RFOS_CORE_SOURCES
    src/menuitem.cpp
    src/menu.cpp
    src/orderitem.cpp
    src/order.cpp
    src/bill.cpp
    src/inputhandler.cpp
)

add_library(rfos_core ${RFOS_CORE_SOURCES})
target_include_directories(rfos_core PUBLIC include)

add_executable(rfos
    src/main.cpp
    src/consoleui.cpp
)
target_link_libraries(rfos PRIVATE rfos_core)

option(RFOS_BUILD_TESTS "Build RFOS tests" ON)

if(RFOS_BUILD_TESTS)
    enable_testing()
    add_executable(rfos_tests tests/rfos_tests.cpp)
    target_link_libraries(rfos_tests PRIVATE rfos_core)
    add_test(NAME RFOS_CoreTests COMMAND rfos_tests)
endif()

if(MSVC)
    target_compile_options(rfos_core PRIVATE /W4)
    target_compile_options(rfos PRIVATE /W4)
    if(TARGET rfos_tests)
        target_compile_options(rfos_tests PRIVATE /W4)
    endif()
else()
    target_compile_options(rfos_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(rfos PRIVATE -Wall -Wextra -Wpedantic)
    if(TARGET rfos_tests)
        target_compile_options(rfos_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()
