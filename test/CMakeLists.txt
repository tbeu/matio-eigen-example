project(${CMAKE_PROJECT_NAME}Tests LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})

conan_cmake_configure(
  REQUIRES "gtest/1.14.0"
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

find_package(GTest REQUIRED)
include(GoogleTest)

set(TEST_SOURCES src/example_test.cpp)

foreach(file ${TEST_SOURCES})
  string(REGEX REPLACE "(.*/)([a-zA-Z0-9_ ]+)(\.cpp)" "\\2" test_name ${file})
  add_executable(${test_name}_Tests ${file})
  target_include_directories(${test_name}_Tests PRIVATE "${CMAKE_SOURCE_DIR}/include")
  target_link_libraries(${test_name}_Tests PRIVATE example GTest::GTest)
  target_compile_features(${test_name}_Tests PUBLIC cxx_std_17)
  set_target_properties(${test_name}_Tests PROPERTIES CXX_EXTENSIONS OFF)
  gtest_add_tests(
    TARGET ${test_name}_Tests
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")
endforeach()
