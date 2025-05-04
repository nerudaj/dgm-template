cmake_minimum_required ( VERSION 3.26 )

make_executable ( ${PROJECT_NAME} DEPS cxxopts ${LIB_TARGET_NAME} )

set_target_properties ( ${PROJECT_NAME} PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    WIN32_EXECUTABLE ON
)

# Packaging
install (
	FILES       "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/${THE_PROJECT_NAME}.exe"
	DESTINATION "bin"
)

file ( GLOB DLLS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/*.dll" )

install (
	FILES       ${DLLS}
	DESTINATION "bin"
)
