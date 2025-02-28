set ( CXXOPTS_VERSION "3.2.1" )
set ( NLOHMANN_VERSION "3.11.3" )
set ( SFML_VERSION "3.0.0" )
set ( DGM_LIB_VERSION "3.0.0-rc4" )
set ( FSM_LIB_VERSION "2.1.1" )
set ( TGUI_VERSION "1.7.0" )
set ( CATCH2_VERSION "v3.8.0" )

CPMAddPackage("gh:jarro2783/cxxopts#v${CXXOPTS_VERSION}")
CPMAddPackage("gh:nlohmann/json#v${NLOHMANN_VERSION}")

message ( "=== FETCHING PREBUILT DEPENDENCIES ===")

fetch_prebuilt_dependency(
    SFML
	URL https://github.com/SFML/SFML/releases/download/${SFML_VERSION}/SFML-${SFML_VERSION}-windows-vc17-64-bit.zip
)

message ( "==== SFML DOWNLOADED ===" )

fetch_prebuilt_dependency (
    DGM
    URL https://github.com/nerudaj/dgm-lib/releases/download/v${DGM_LIB_VERSION}/dgm-lib-v${DGM_LIB_VERSION}-Windows-x64-MSVC-143-for-SFML-${SFML_VERSION}.zip
)

message ( "==== DGM-LIB DOWNLOADED ===" )

fetch_prebuilt_dependency (
    FSM
    URL https://github.com/nerudaj/fsm-lib/releases/download/v${FSM_LIB_VERSION}/fsm-lib-v${FSM_LIB_VERSION}-Windows-MSVC-x64.zip
)


message ( "==== FSM-LIB DOWNLOADED ===" )

fetch_prebuilt_dependency (
    TGUI
    URL https://github.com/texus/TGUI/releases/download/v${TGUI_VERSION}/TGUI-${TGUI_VERSION}-vc17-64bit-for-SFML-${SFML_VERSION}.zip
)

set ( TGUI_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/_deps/TGUI-src" )

message ( "==== TGUI DOWNLOADED ===" )

set ( CATCH2_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/_deps/catch2" )
make_directory( "${CATCH2_FOLDER}/include" )

file ( DOWNLOAD
    https://github.com/catchorg/Catch2/releases/download/${CATCH2_VERSION}/catch_amalgamated.hpp
    "${CATCH2_FOLDER}/include/catch_amalgamated.hpp"
)

file ( DOWNLOAD
    https://github.com/catchorg/Catch2/releases/download/${CATCH2_VERSION}/catch_amalgamated.cpp
    "${CATCH2_FOLDER}/catch_amalgamated.cpp"
)

message ( "==== CATCH2 DOWNLOADED ===" )

message ( "=== FETCHING OK ===" )

set ( SFML_STATIC_LIBRARIES ${USE_SFML_TGUI_STATIC_LINKAGE} )
find_package ( SFML
    ${SFML_VERSION} REQUIRED
    COMPONENTS Main Window Graphics
    PATHS "${SFML_FOLDER}/lib/cmake"
)

set ( TGUI_BACKEND SFML_GRAPHICS )
set ( TGUI_STATIC_LIBRARIES ${USE_SFML_TGUI_STATIC_LINKAGE} )
find_package ( TGUI 
    ${TGUI_VERSION} REQUIRED
    PATHS "${TGUI_FOLDER}/lib/cmake"
)

find_package ( dgm-lib
    ${DGM_LIB_VERSION} REQUIRED
    PATHS "${DGM_FOLDER}/lib/cmake"
)

find_package ( fsm-lib
    ${FSM_LIB_VERSION} REQUIRED
    PATHS "${FSM_FOLDER}/lib/cmake"
)


if ( ${BUILD_TESTS} )
    add_library ( catch2 STATIC "${CATCH2_FOLDER}/include/catch2/catch_all.hpp" "${CATCH2_FOLDER}/catch_amalgamated.cpp" )
    target_include_directories( catch2 PUBLIC "${CATCH2_FOLDER}/include" )
    message ( "=== CATCH CONFIGURED ===" )
endif ()
