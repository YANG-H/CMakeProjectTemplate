# construct dependencies
#   DEPENDENCY_INCLUDES
#   DEPENDENCY_LIBS
#   DEPENDENCY_BIN_PATHS
#   TEST_DEPENDENCY_INCLUDES
#   TEST_DEPENDENCY_LIBS
#   TEST_DEPENDENCY_BIN_PATHS

set (_DEPENDENCY_NAMES "")
set (_DEPENDENCY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
set (_DEPENDENCY_LIBS "")
set (_DEPENDENCY_BIN_PATHS "")

# uncomment this to enable cereal dependency
# add_subdirectory("cereal")
# list (APPEND _DEPENDENCY_NAMES "cereal")
# list (APPEND _DEPENDENCY_INCLUDES ${CEREAL_INCLUDES})
# if (MSVC)
#     add_definitions ( "/D${PROJECT_NAME}_WITH_CEREAL" )
# else ()
#     add_definitions ( "-D${PROJECT_NAME}_WITH_CEREAL" )
# endif ()

# uncomment this to enable eigen3 dependency
# add_subdirectory("eigen3")
# list (APPEND _DEPENDENCY_NAMES "eigen3")
# list (APPEND _DEPENDENCY_INCLUDES ${EIGEN3_INCLUDES})
# if (MSVC)
#     add_definitions ( "/D${PROJECT_NAME}_WITH_EIGEN3" )
# else ()
#     add_definitions ( "-D${PROJECT_NAME}_WITH_EIGEN3" )
# endif ()

# uncomment this to enable openblas dependency
# find_package(OpenBLAS REQUIRED)
# if (${OpenBLAS_FOUND})
# 	list (APPEND _DEPENDENCY_INCLUDES ${OpenBLAS_INCLUDE_DIR})
#     list (APPEND _DEPENDENCY_LIBS ${OpenBLAS_LIB})
#     list (APPEND _DEPENDENCY_BIN_PATHS ${OpenBLAS_DIR}/bin)
#     if (MSVC)
#         add_definitions ( "/D${PROJECT_NAME}_WITH_OPENBLAS" )
#     else ()
#         add_definitions ( "-D${PROJECT_NAME}_WITH_OPENBLAS" )
#     endif ()
# endif()

# uncomment this to enable opencv dependency
# find_package(OpenCV REQUIRED)
# if (${OpenCV_FOUND})
#     list (APPEND _DEPENDENCY_INCLUDES ${OpenCV_INCLUDE_DIRS})
#     list (APPEND _DEPENDENCY_LIBS ${OpenCV_LIBS})
#     list (APPEND _DEPENDENCY_BIN_PATHS ${_OpenCV_LIB_PATH})
#     if (MSVC)
#         add_definitions ( "/D${PROJECT_NAME}_WITH_OPENCV" )
#     else ()
#         add_definitions ( "-D${PROJECT_NAME}_WITH_OPENCV" )
#     endif ()
# endif()

# uncomment this to enable matlab dependency
# find_package(MATLAB REQUIRED)
# if (${MATLAB_FOUND})
#     #  MATLAB_INCLUDE_DIR: include path for mex.h, engine.h
#     #  MATLAB_LIBRARIES:   required libraries: libmex, etc
#     #  MATLAB_MEX_LIBRARY: path to libmex.lib
#     #  MATLAB_MX_LIBRARY:  path to libmx.lib
#     #  MATLAB_MAT_LIBRARY:  path to libmat.lib # added
#     #  MATLAB_ENG_LIBRARY: path to libeng.lib
#     #  MATLAB_ROOT: path to Matlab's root directory
#     list (APPEND _DEPENDENCY_INCLUDES ${MATLAB_INCLUDE_DIR})
#     list (APPEND _DEPENDENCY_LIBS ${MATLAB_LIBRARIES})
#     list (APPEND _DEPENDENCY_LIBS ${MATLAB_MAT_LIBRARY})
#     if (MSVC)
#         add_definitions ( "/D${PROJECT_NAME}_WITH_MATLAB" )
#     else ()
#         add_definitions ( "-D${PROJECT_NAME}_WITH_MATLAB" )
#     endif ()
# endif()


set (DEPENDENCY_NAMES ${_DEPENDENCY_NAMES} PARENT_SCOPE)
set (DEPENDENCY_INCLUDES ${_DEPENDENCY_INCLUDES} PARENT_SCOPE)
set (DEPENDENCY_LIBS ${_DEPENDENCY_LIBS} PARENT_SCOPE)
set (DEPENDENCY_BIN_PATHS ${_DEPENDENCY_BIN_PATHS} PARENT_SCOPE)

if (${BuildUnitTest})   
    add_subdirectory("googletest")
    set (TEST_DEPENDENCY_NAMES "googletest" PARENT_SCOPE)
    set (TEST_DEPENDENCY_INCLUDES ${GTEST_INCLUDES} PARENT_SCOPE)
    set (TEST_DEPENDENCY_LIBS ${GTEST_LIBS} PARENT_SCOPE)
    set (TEST_DEPENDENCY_BIN_PATHS "" PARENT_SCOPE)
endif()