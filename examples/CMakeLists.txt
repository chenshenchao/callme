message(STATUS "[callme] build examples.")

add_subdirectory(lexer_demo)
add_subdirectory(parser_demo)

install(
	TARGETS
    lexer_demo
    parser_demo
	RUNTIME DESTINATION "bin"
    ARCHIVE DESTINATION "lib"
    LIBRARY DESTINATION "bin"
    INCLUDES DESTINATION "inc"
)
