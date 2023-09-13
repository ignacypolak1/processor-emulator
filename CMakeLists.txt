cmake_minimum_required(VERSION 3.26)
project(processor-emulator)

set(CMAKE_CXX_STANDARD 17)

# Include header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include source files
file(GLOB SOURCE_FILES src/*.cpp)
add_executable(processor-emulator ${SOURCE_FILES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(processor-emulator PROPERTIES VS_JUST_MY_CODE_DEBUGGING YES)
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Og -O0")
    add_definitions(-DDEBUG)
else ()
    # something else later
endif()
