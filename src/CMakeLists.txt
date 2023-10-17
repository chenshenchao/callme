add_library(callme ${CALLME_TARGET_TYPE})
add_library(callme::callme ALIAS callme)

set(CALLME_DIR ${CMAKE_CURRENT_LIST_DIR})
message(STATUS "[callme] dir: ${CALLME_DIR}")

set_target_properties(
	callme
	PROPERTIES
	LINKER_LANGUAGE CXX
    CXX_STANDARD 11
)

if (CALLME_STATIC)
	target_compile_definitions(
		callme
		PUBLIC
		CALLME_STATIC
	)
else()
	target_compile_definitions(
		callme
		PRIVATE
		CALLME_EXPORT
	)
endif()

target_link_libraries(callme asmjit::asmjit)

file(GLOB_RECURSE CALLME_CPP_FILES "callme/*.cpp")
file(GLOB_RECURSE CALLME_H_FILES "*.h")

message(STATUS "[callme] src: ${CALLME_CPP_FILES}")

target_sources(
	callme
	PRIVATE
    ${CALLME_H_FILES}
    ${CALLME_CPP_FILES}
)

# 导出头文件
target_include_directories(
    callme BEFORE INTERFACE
    $<BUILD_INTERFACE:${CALLME_DIR}>
    $<INSTALL_INTERFACE:inc>
)

# 安装生成文件
install(
	TARGETS callme
	EXPORT callme-config
	RUNTIME DESTINATION "bin"
    ARCHIVE DESTINATION "lib"
    LIBRARY DESTINATION "bin"
    INCLUDES DESTINATION "inc"
)

# 安装头文件
foreach(H_FILE_PATH ${CALLME_H_FILES})
    if (NOT ${H_FILE_PATH} MATCHES "_i\\.h$")
        get_filename_component(H_FILE_ABS_DIR ${H_FILE_PATH} PATH)
        file(RELATIVE_PATH H_FILE_DIR ${CALLME_DIR} ${H_FILE_ABS_DIR})
        set(H_FILE_OUT_DIR "inc/${H_FILE_DIR}")
        install(
            FILES
            ${H_FILE_PATH}
            DESTINATION
            ${H_FILE_OUT_DIR}
        )
        message(STATUS "[callme] install h: ${H_FILE_PATH} => ${H_FILE_OUT_DIR}")
    endif()
endforeach()

# 安装命名空间
install(
	EXPORT callme-config
	NAMESPACE callme::
	DESTINATION "cmake"
)
