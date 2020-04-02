cmake_minimum_required(VERSION 3.15)
project(crypto_test_app)

set(CMAKE_CXX_STANDARD 11)

## ensure unix environment (CMAKE_SYSTEM_NAME == "Linux")
if((NOT UNIX) OR (NOT ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")))
    message(FATAL_ERROR "Unix/Linux environment is required.")
endif()
## ensure out-of-source build
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "An out-of-source build is required. Please see the README.")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
## we need to know where shadow is installed
if("${SHADOW_ROOT}" STREQUAL "")
    set(SHADOW_ROOT "$ENV{HOME}/.shadow")
endif()
if(EXISTS "${SHADOW_ROOT}")
    message(STATUS "SHADOW_ROOT = ${SHADOW_ROOT}")
else()
    message(FATAL_ERROR "SHADOW_ROOT path does not exist: '${SHADOW_ROOT}'")
endif()
## by default, install to SHADOW_ROOT
if(NOT ${CMAKE_INSTALL_PREFIX})
    set(CMAKE_INSTALL_PREFIX "${SHADOW_ROOT}")
endif()
if(EXISTS "${SHADOW_ROOT}/share/cmake/Modules")
    set(CMAKE_MODULE_PATH "${SHADOW_ROOT}/share/cmake/Modules" ${CMAKE_MODULE_PATH})
endif()

include(ShadowTools)

set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")
add_compile_options(-ggdb)
add_compile_options(-fno-omit-frame-pointer)
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-DDEBUG)
add_compile_options(-O0)

add_executable(crypto_test_app main.cpp)
add_shadow_plugin(crypto_test_lib main.cpp)
target_link_libraries(crypto_test_app ssl crypto)
target_link_libraries(crypto_test_lib ssl crypto)




