message(STATUS "[callme] build examples.")

set(CALLME_EXAMPLES_ASSETS_DIR "${CMAKE_CURRENT_LIST_DIR}/assets")

add_subdirectory(lexer_demo)
add_subdirectory(parser_demo)
add_subdirectory(interpreter_demo)

install(
	TARGETS
    lexer_demo
    parser_demo
    interpreter_demo
	RUNTIME DESTINATION "bin"
    ARCHIVE DESTINATION "lib"
    LIBRARY DESTINATION "bin"
    INCLUDES DESTINATION "inc"
)
