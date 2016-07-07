cmake_minimum_required(VERSION 3.0.0)
project(WheelsProxy C CXX)
include(ExternalProject)

ExternalProject_Add(wheels
     URL "file://${CMAKE_CURRENT_SOURCE_DIR}/wheels-master.zip"
     CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs 
               -DBuildUnitTest=off
               -DUSE_AUXMATH=off
               -DUSE_MATLAB=off
               -DUSE_OPENCV=off
               -DUSE_EIGEN=off
               -DUSE_IMAGE=on
     PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
     STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}"
# Disable install step
     INSTALL_COMMAND ""
)

# Specify include dir
ExternalProject_Get_Property(wheels source_dir)
set(WHEELS_INCLUDES "${source_dir}" PARENT_SCOPE)

# Specify libs
ExternalProject_Get_Property(wheels binary_dir)
set(WHEELS_LIBS_DIR ${binary_dir})
if(NOT MSVC)
    set(WHEELS_LIBS 
        ${WHEELS_LIBS_DIR}/libwheels.a
        PARENT_SCOPE)
else()
    set(WHEELS_LIBS
        debug "${WHEELS_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}wheels${CMAKE_FIND_LIBRARY_SUFFIXES}"
        optimized "${WHEELS_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}wheels${CMAKE_FIND_LIBRARY_SUFFIXES}"
        PARENT_SCOPE)
endif()