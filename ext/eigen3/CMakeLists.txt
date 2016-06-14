cmake_minimum_required(VERSION 3.0.0)
project(Eigen3Proxy C CXX)
include(ExternalProject)

ExternalProject_Add(eigen3
     URL "file://${CMAKE_CURRENT_SOURCE_DIR}/eigen.zip"
     PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
     STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}"
     CONFIGURE_COMMAND ""
     BUILD_COMMAND ""
# Disable install step
     INSTALL_COMMAND ""
)

# Specify include dir
ExternalProject_Get_Property(eigen3 source_dir)
set(EIGEN3_INCLUDES "${source_dir}" PARENT_SCOPE)
