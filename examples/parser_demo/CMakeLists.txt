add_executable(parser_demo)

target_sources(
	parser_demo
	PRIVATE
	"main.cpp"
)

set_target_properties(
	parser_demo
	PROPERTIES
	LINKER_LANGUAGE CXX
    CXX_STANDARD 20
)

target_link_libraries(
    parser_demo
    callme::callme
)

add_custom_command(
    TARGET parser_demo
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${CALLME_EXAMPLES_ASSETS_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
)
