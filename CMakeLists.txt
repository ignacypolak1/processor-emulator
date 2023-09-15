cmake_minimum_required(VERSION 3.26)
project(processor-emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include source files to library
add_library(cpu6502 STATIC
        lib/cpu6502/src/processor.cpp
        lib/cpu6502/src/instructions.cpp
)

# Include library headers to library
target_include_directories(cpu6502 PUBLIC lib/cpu6502/include)

# Include header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include source files
file(GLOB SOURCE_FILES src/*.cpp)

add_executable(processor-emulator ${SOURCE_FILES})
target_link_libraries(processor-emulator cpu6502)

# Tests
include(FetchContent)
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
        cpu6502
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
