cmake_minimum_required ( VERSION 3.26 )

include ( "cmake/vars.cmake" )
include ( "cmake/cpp-init.cmake" )

cpp_init()
get_version_from_git ( PROJECT_VERSION_VARIABLE GIT_FULL_VERSION )

project ( ${THE_PROJECT_NAME} VERSION ${PROJECT_VERSION_VARIABLE} )

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Compiled" )

option ( BUILD_TESTS "Build unit testing target" ON )
option ( BUILD_ANDROID "Perform Android build instead of Windows" OFF )
option ( USE_NSIS "Use NSIS for packaging" OFF )

include ( "cmake/dependencies.cmake" )

if ( ${BUILD_ANDROID} )
    add_subdirectory( "android" )
else ()
    add_subdirectory ( "lib" )
    add_subdirectory ( "bin" )

    if ( ${BUILD_TESTS} )
        enable_testing()
        add_subdirectory ( "tests" )
    endif ()
endif ()

# TODO: packaging

include ( CPack )
