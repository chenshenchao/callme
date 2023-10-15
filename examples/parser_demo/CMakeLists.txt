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
    CXX_STANDARD 11
)

target_link_libraries(
    parser_demo
    callme::callme
)
