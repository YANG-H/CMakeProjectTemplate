set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (sources "")
set (test_sources "")

file (GLOB sources 
    "*.cpp" 
    "*.hpp"
    "*.c" 
    "*.h"
)
file (GLOB test_sources
    "*.test.cpp" 
    "*.test.hpp"
    "*.test.c" 
    "*.test.h"
)

file (GLOB entry_sources main.cpp lib.cpp unittest.cpp)

# remove entry cpp files
list (REMOVE_ITEM sources ${entry_sources})

# remove test sources from sources
if (test_sources)
    list (REMOVE_ITEM sources ${test_sources})
endif ()

source_group ("Sources" FILES ${sources})
source_group ("Sources" FILES ${test_sources})

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
if (DEPENDENCY_NAMES)
    add_dependencies(${PROJECT_NAME}.Lib ${DEPENDENCY_NAMES})
endif ()

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