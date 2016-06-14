set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (sources "")
set (test_sources "")

file (GLOB sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)
file (GLOB test_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.test.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.test.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.test.c" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.test.h"
)

# remove test sources from sources
list (REMOVE_ITEM sources ${test_sources})

source_group ("src" FILES ${sources})
source_group ("src" FILES ${test_sources})

# tips for msvc
if (MSVC)
    message (WARNING "CMake cannot configure Visual Studio to"
        " modify the environment path during program execution, "
        "therefore you have to do this manually: "
        "add 'PATH=${DEPENDENCY_BIN_PATHS};$(PATH);' "
        "to [Project Property]->[Debug]->[Environment] ")
endif ()

foreach (i ${DEPENDENCY_INCLUDES})
    message (STATUS "DEPENDENCY_INCLUDES: ${i}")
endforeach ()

# the lib
message(STATUS "sources:")
foreach(i ${sources})
    message (STATUS ${i})  
endforeach()
add_library(${PROJECT_NAME}.Lib ${sources} ./lib.cpp)
target_include_directories (${PROJECT_NAME}.Lib PUBLIC ${DEPENDENCY_INCLUDES})
target_link_libraries (${PROJECT_NAME}.Lib ${DEPENDENCY_LIBS})
add_dependencies(${PROJECT_NAME}.Lib ${DEPENDENCY_NAMES})

# the unit tests
if (${BuildUnitTest})
    message(STATUS "test sources:")
    foreach(i ${test_sources})   
        message (STATUS ${i})  
    endforeach()
    
    enable_testing()    
    add_executable(${PROJECT_NAME}.UnitTest ${test_sources} ./unittest.cpp)
    target_include_directories (${PROJECT_NAME}.UnitTest PUBLIC
        ${DEPENDENCY_INCLUDES} ${TEST_DEPENDENCY_INCLUDES})
    target_link_libraries (${PROJECT_NAME}.UnitTest ${PROJECT_NAME}.Lib)
    target_link_libraries (${PROJECT_NAME}.UnitTest ${DEPENDENCY_LIBS})
    target_link_libraries (${PROJECT_NAME}.UnitTest ${TEST_DEPENDENCY_LIBS})
    add_dependencies(${PROJECT_NAME}.UnitTest ${PROJECT_NAME}.Lib 
        ${DEPENDENCY_NAMES} ${TEST_DEPENDENCY_NAMES})
endif ()

# the executible 
if (${BuildExecutable})
    add_executable(${PROJECT_NAME}.Exe ${sources} ./main.cpp)
    target_include_directories (${PROJECT_NAME}.Exe PUBLIC ${DEPENDENCY_INCLUDES})
    target_link_libraries (${PROJECT_NAME}.Exe ${PROJECT_NAME}.Lib)
    target_link_libraries (${PROJECT_NAME}.Exe ${DEPENDENCY_LIBS})
    add_dependencies(${PROJECT_NAME}.UnitTest ${PROJECT_NAME}.Lib 
        ${DEPENDENCY_NAMES})
endif ()