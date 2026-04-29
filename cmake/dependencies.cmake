include ( "${CMAKE_CURRENT_LIST_DIR}/add-catch.cmake" )

set ( CXXOPTS_VERSION "3.3.1" )
set ( FSM_LIB_VERSION "main" )
set ( CATCH2_VERSION "v3.8.0" )

CPMAddPackage("gh:jarro2783/cxxopts#v${CXXOPTS_VERSION}")

CPMAddPackage("gh:nerudaj/fsm-lib#${FSM_LIB_VERSION}")
AddCatch( "${CATCH2_VERSION}" )
