project(${CMAKE_PROJECT_NAME}Tests LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.16.0
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

set(TEST_SOURCES src/example_test.cpp)
foreach(file ${TEST_SOURCES})
  string(REGEX REPLACE "(.*/)([a-zA-Z0-9_ ]+)(\.cpp)" "\\2" TEST_NAME ${file})
  add_executable(${TEST_NAME}Tests ${file})
  target_include_directories(${TEST_NAME}Tests PRIVATE "${CMAKE_SOURCE_DIR}/include")
  target_link_libraries(${TEST_NAME}Tests PRIVATE ${EXAMPLE_LIB_NAME} gtest gtest_main)
  target_compile_features(${TEST_NAME}Tests PUBLIC cxx_std_17)
  set_target_properties(${TEST_NAME}Tests PROPERTIES CXX_EXTENSIONS OFF)
  add_test(
    NAME ${TEST_NAME}Tests
    COMMAND ${TEST_NAME}Tests
     WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test"
  )
endforeach()
