cmake_minimum_required ( VERSION 3.26 )

make_executable ( ${PROJECT_NAME} DEPS cxxopts ${LIB_TARGET_NAME} )

set_target_properties ( ${PROJECT_NAME} PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    WIN32_EXECUTABLE ON
)