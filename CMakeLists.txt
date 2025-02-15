cmake_minimum_required(VERSION 3.24)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(MatioEigenExample C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(LIBS_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs)
set(EIGEN_MATIO_URL https://raw.githubusercontent.com/tbeu/eigen-matio/master/MATio)
set(EIGEN_MATIO_DIR ${LIBS_DIR}/include)
set(EIGEN_MATIO_DEST ${EIGEN_MATIO_DIR}/MATio)
if(NOT EXISTS EIGEN_MATIO_DEST)
  file(DOWNLOAD ${EIGEN_MATIO_URL} ${EIGEN_MATIO_DEST})
endif()

find_package(matio REQUIRED)
find_package(Eigen3 REQUIRED)

set(EXAMPLE_LIB_NAME matioEigenExampleLib)
add_library(${EXAMPLE_LIB_NAME} STATIC src/example.cpp include/example.hpp)
target_include_directories(${EXAMPLE_LIB_NAME} PRIVATE ${EIGEN_MATIO_DIR})
target_link_libraries(${EXAMPLE_LIB_NAME} PRIVATE matio::matio Eigen3::Eigen)
target_compile_features(${EXAMPLE_LIB_NAME} PUBLIC cxx_std_17)
set_target_properties(${EXAMPLE_LIB_NAME} PROPERTIES CXX_EXTENSIONS OFF)

enable_testing()
add_subdirectory(test)
