cmake_minimum_required(VERSION 3.26)
project(processor-emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)

# OpenGL
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
)
FetchContent_GetProperties(glfw)

if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
)

FetchContent_GetProperties(glew)

if(NOT glew_POPULATED)
    FetchContent_Populate(glew)
    set(BUILD_UTILS OFF CACHE INTERNAL "Build utility executables")
    add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR})
endif()

# Include source files to library
add_library(cpu6510 STATIC
        lib/cpu6510/src/processor.cpp
        lib/cpu6510/src/instructions.cpp
        lib/cpu6510/src/memory.cpp
        lib/cpu6510/src/vic2.cpp
)

# Include library headers to library
target_include_directories(cpu6510 PUBLIC lib/cpu6510/include)

# Include header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include OpenGL
target_link_libraries(cpu6510 glfw libglew_static)

# Include source files
file(GLOB SOURCE_FILES src/*.cpp)

add_executable(processor-emulator ${SOURCE_FILES})
target_link_libraries(processor-emulator cpu6510)

# Tests
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(
        processor_test
        test/test.cc
)
target_link_libraries(
        processor_test
        GTest::gtest_main
        cpu6510
)
include(GoogleTest)
gtest_discover_tests(processor_test)

add_dependencies(processor-emulator processor_test)
add_custom_target(run_tests ALL
    COMMAND processor_test
    DEPENDS processor_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_dependencies(processor-emulator run_tests)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(processor-emulator PROPERTIES VS_JUST_MY_CODE_DEBUGGING YES)
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Og -O0")
    add_definitions(-DDEBUG)
else ()
    # something else later
endif()
