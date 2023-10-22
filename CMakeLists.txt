cmake_minimum_required(VERSION 3.24)

# 选项
option(CALLME_BUILD_EXAMPLES "build callme examples." OFF)
option(CALLME_STATIC "build callme static" ON)

include("cmake/AsmJit.cmake")

if (CALLME_STATIC)
    set(CALLME_TARGET_TYPE "STATIC")
else()
    set(CALLME_TARGET_TYPE "SHARED")
endif()

project(callme CXX)
message(STATUS "[callme] project cxx")

ImportAsmJit()

add_subdirectory(src)
if (CALLME_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
