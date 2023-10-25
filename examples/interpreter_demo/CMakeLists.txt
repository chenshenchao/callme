add_executable(interpreter_demo)

target_sources(
	interpreter_demo
	PRIVATE
	"main.cpp"
)

set_target_properties(
	interpreter_demo
	PROPERTIES
	LINKER_LANGUAGE CXX
    CXX_STANDARD 20
)

target_link_libraries(interpreter_demo callme::callme)

add_custom_command(
    TARGET interpreter_demo
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${CALLME_EXAMPLES_ASSETS_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
)
