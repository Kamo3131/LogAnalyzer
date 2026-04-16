cmake_minimum_required(VERSION 3.24)
project(my_project C CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(TESTS_DIR "${PROJECT_SOURCE_DIR}/tests")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")
add_library(app_logic ${SOURCES})
target_include_directories(app_logic PUBLIC ${INCLUDE_DIR})
# Universal path so I can easly locate files.
set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DPROJECT_ROOT_DIR="${ROOT_DIR}")
target_compile_definitions(app_logic PRIVATE PROJECT_ROOT_DIR="${ROOT_DIR}")

add_executable(${PROJECT_NAME} Main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE app_logic)

enable_testing()
file(GLOB_RECURSE TESTS "${TESTS_DIR}/*.cpp")
add_executable(tests ${TESTS})

target_link_libraries(
  tests PRIVATE app_logic GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
