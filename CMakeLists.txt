cmake_minimum_required(VERSION 3.10...3.29)
project(softloq-whatwg-encoding-project VERSION 1.0.0 LANGUAGES CXX)
option(BUILD_SHARED_LIBS "Generate shared library" OFF)
option(SOFTLOQ_WHATWG_ENCODING_BUILD_TESTING "Generate unit-testing" OFF)
option(SOFTLOQ_WHATWG_ENCODING_MONOLITHIC_BUILD "Builds everything in one library" OFF)

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
include(FindThreads)

# Library build
if(SOFTLOQ_WHATWG_ENCODING_MONOLITHIC_BUILD)
    # Builds everything in one library
    file(GLOB_RECURSE SOFTLOQ_WHATWG_ENCODING_MONOLITHIC_CXX_FILES softloq-whatwg-infra/src/**.cpp)
    set(SOFTLOQ_WHATWG_ENCODING_MONOLITHIC_PUBLIC_INCLUDES softloq-whatwg-infra/include)
    if(SOFTLOQ_WHATWG_ENCODING_BUILD_SHARED)
        list(APPEND SOFTLOQ_WHATWG_ENCODING_PUBLIC_DEFINITIONS SOFTLOQ_WHATWG_INFRA_USE_API)
        list(APPEND SOFTLOQ_WHATWG_ENCODING_PRIVATE_DEFINITIONS SOFTLOQ_WHATWG_INFRA_BUILD_API)
    endif()
else()
    # Build dependencies as separate libraries
    list(APPEND SOFTLOQ_WHATWG_ENCODING_DEPENDENCIES softloq::whatwg-infra)
    list(APPEND SOFTLOQ_WHATWG_ENCODING_LINK_LIBRARIES softloq::whatwg-infra)
    if(NOT TARGET softloq-whatwg-infra)
        add_subdirectory(softloq-whatwg-infra)
    endif()
endif()

if(NOT TARGET softloq-whatwg-encoding)
    file(GLOB_RECURSE CXX_FILES src/**.cpp)
    add_library(softloq-whatwg-encoding ${LIBRARY_TYPE} ${CXX_FILES})
    add_library(softloq::whatwg-encoding ALIAS softloq-whatwg-encoding)
    if(SOFTLOQ_WHATWG_ENCODING_DEPENDENCIES)
    add_dependencies(softloq-whatwg-encoding ${SOFTLOQ_WHATWG_ENCODING_DEPENDENCIES})
    endif()
    target_include_directories(softloq-whatwg-encoding PUBLIC include ${SOFTLOQ_WHATWG_ENCODING_MONOLITHIC_PUBLIC_INCLUDES})
    target_compile_definitions(softloq-whatwg-encoding PUBLIC ${PUBLIC_DEFINITIONS})
    target_compile_definitions(softloq-whatwg-encoding PRIVATE ${PRIVATE_DEFINITIONS})
    target_link_libraries(softloq-whatwg-encoding PUBLIC ${SOFTLOQ_WHATWG_ENCODING_LINK_LIBRARIES})
    target_link_libraries(softloq-whatwg-encoding PRIVATE Threads::Threads)
endif()

# Unit testing
if(BUILD_TESTING AND SOFTLOQ_WHATWG_ENCODING_BUILD_TESTING)
    add_executable(softloq-whatwg-encoding-test tests/example.cpp)
    add_dependencies(softloq-whatwg-encoding-test softloq::whatwg-encoding)
    target_link_libraries(softloq-whatwg-encoding-test softloq::whatwg-encoding Threads::Threads)
endif()
