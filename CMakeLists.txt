cmake_minimum_required (VERSION 3.0)
PROJECT (XXX VERSION 0.1 LANGUAGES CXX) # set the project name here!

option (BuildUnitTest "build UnitTest" on)
option (BuildExecutable "build Executable" on)

set (CMAKE_ALLOW_LOOSE_CONSTRUCTS true)
list (APPEND CMAKE_MODULE_PATH 
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    message (STATUS "Clang: ${CLANG_VERSION_STRING}")
    if(CLANG_VERSION_STRING VERSION_GREATER 3.5)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    else()
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
    endif()
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    message (STATUS "GCC: ${GCC_VERSION}")
    if (NOT (GCC_VERSION VERSION_GREATER 4.9 OR GCC_VERSION VERSION_EQUAL 4.9))
        message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.9 or greater.")
    endif ()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()


add_subdirectory (ext)

add_subdirectory (src)