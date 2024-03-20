cmake_minimum_required(VERSION 3.11)

project(MatioEigenExample C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
       "${CMAKE_BINARY_DIR}/conan.cmake" TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

set(LIBS_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs)
set(EIGEN_MATIO_URL https://raw.githubusercontent.com/tesch1/eigen-matio/master/MATio)
set(EIGEN_MATIO_DIR ${LIBS_DIR}/include)
set(EIGEN_MATIO_DEST ${EIGEN_MATIO_DIR}/MATio)
if(NOT EXISTS EIGEN_MATIO_DEST)
  file(DOWNLOAD ${EIGEN_MATIO_URL} ${EIGEN_MATIO_DEST})
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})

conan_cmake_configure(
  REQUIRES "matio/[>=1.5.24]" "eigen/[>=3.4.0]"
  GENERATORS cmake_find_package)
conan_cmake_autodetect(settings)
conan_add_remote(
  NAME conan-center
  URL https://center.conan.io
  VERIFY_SSL False)
conan_cmake_install(
  PATH_OR_REFERENCE .
  BUILD missing
  REMOTE conan-center
  SETTINGS ${settings})

find_package(matio REQUIRED)
find_package(Eigen3 REQUIRED)

add_library(example STATIC src/example.cpp include/example.hpp)
target_include_directories(example PRIVATE ${EIGEN_MATIO_DIR})
target_link_libraries(example PRIVATE matio::matio Eigen3::Eigen)
target_compile_features(example PUBLIC cxx_std_17)
set_target_properties(example PROPERTIES CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(test)
