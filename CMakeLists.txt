cmake_minimum_required(VERSION 3.24)

# 选项
option(CALLME_BUILD_EXAMPLES "build callme examples." OFF)
option(CALLME_STATIC "build callme static" OFF)

project(callme CXX)
message(STATUS "[callme] project cxx")

add_subdirectory(src)
if (CALLME_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
