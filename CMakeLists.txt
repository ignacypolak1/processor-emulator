cmake_minimum_required(VERSION 3.26)
project(processor-emulator)

set(CMAKE_CXX_STANDARD 17)

# Include header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include source files
file(GLOB SOURCE_FILES src/*.cpp)
add_executable(processor-emulator ${SOURCE_FILES})
