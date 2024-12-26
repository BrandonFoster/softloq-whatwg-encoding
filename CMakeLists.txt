cmake_minimum_required(VERSION 3.10...3.29)
project(softloq-whatwg-encoding-project VERSION 1.0.0 LANGUAGES CXX)
option(BUILD_SHARED_LIBS "Generate Shared Library" OFF)
option(SOFTLOQ_WHATWG_ENCODING_BUILD_TESTING "Generate Unit-Testing" OFF)

# Build settings
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
endif()
if(NOT CMAKE_CXX_STANDARD_REQUIRED)
    set(CMAKE_CXX_STANDARD_REQUIRED)
endif()
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

include(CTest)

# Default values
set(LIBRARY_TYPE STATIC)
set(PUBLIC_DEFINITIONS "")
set(PRIVATE_DEFINITIONS "")

# Library settings
if(BUILD_SHARED_LIBS)
    set(LIBRARY_TYPE SHARED)
    set(PUBLIC_DEFINITIONS SOFTLOQ_WHATWG_ENCODING_USE_API)
    set(PRIVATE_DEFINITIONS SOFTLOQ_WHATWG_ENCODING_BUILD_API)
endif()

# Library build
file(GLOB_RECURSE CXX_FILES src/**.cpp)
add_library(softloq-whatwg-encoding ${LIBRARY_TYPE} ${CXX_FILES})
add_library(softloq::whatwg-encoding ALIAS softloq-whatwg-encoding)
target_include_directories(softloq-whatwg-encoding PUBLIC include)
target_compile_definitions(softloq-whatwg-encoding PUBLIC ${PUBLIC_DEFINITIONS})
target_compile_definitions(softloq-whatwg-encoding PRIVATE ${PRIVATE_DEFINITIONS})

# Unit testing
if(BUILD_TESTING AND SOFTLOQ_WHATWG_ENCODING_BUILD_TESTING)
    add_executable(softloq-whatwg-encoding-test tests/example.cpp)
    add_dependencies(softloq-whatwg-encoding-test softloq::whatwg-encoding)
    target_link_libraries(softloq-whatwg-encoding-test softloq::whatwg-encoding)
endif()
