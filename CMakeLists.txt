cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)

################################
# GTest
################################
ADD_SUBDIRECTORY (googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
if (MSVC)
	set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)
endif  (MSVC)

################################
# Unit Tests
################################
# Add test cpp file
project(runUnitTests)
include_directories(inc)
add_executable( runUnitTests testgtest.cpp)
# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main)
add_test( runUnitTests runUnitTests )

project(DataStrutures)
add_executable(data_strutures src/main.cpp)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT runUnitTests)
endif  (MSVC)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/asd1m.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})