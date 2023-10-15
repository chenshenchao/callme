add_executable(lexer_demo)

target_sources(
	lexer_demo
	PRIVATE
	"main.cpp"
)

set_target_properties(
	lexer_demo
	PROPERTIES
	LINKER_LANGUAGE CXX
    CXX_STANDARD 11
)

target_link_libraries(lexer_demo callme::callme)
