cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0 LANGUAGES C CXX)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("/arch:AVX2")
endif()

include(CTest)
enable_testing()

#json
set(JSONCPP_INCLUDE_DIRS "I:/package/CPPLibs/jsoncpp/dist")
include_directories(${JSONCPP_INCLUDE_DIRS})
file(GLOB json_src ${JSONCPP_INCLUDE_DIRS}/*.cpp)

#Opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS ${JSONCPP_INCLUDE_DIRS})

add_executable(demo main.cpp ${json_src})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
