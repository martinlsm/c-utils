cmake_minimum_required(VERSION 3.17)

project(c-utils)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

add_executable(test-linkedlist test/test-linkedlist.cpp data-structures/linkedlist.c)
target_compile_options(test-linkedlist PRIVATE -g -Wall -Werror)
target_include_directories(test-linkedlist PRIVATE ${PROJECT_SOURCE_DIR}/data-structures/)
target_link_libraries(test-linkedlist gtest_main)
add_test(NAME unittest-linkedlist COMMAND test-linkedlist)

add_executable(test-binaryheap test/test-binaryheap.cpp data-structures/binaryheap.c)
target_compile_options(test-binaryheap PRIVATE -g -Wall -Werror)
target_include_directories(test-binaryheap PRIVATE ${PROJECT_SOURCE_DIR}/data-structures/)
target_link_libraries(test-binaryheap gtest_main)
add_test(NAME unittest-binaryheap COMMAND test-binaryheap)
