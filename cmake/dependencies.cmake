include ( "${CMAKE_CURRENT_LIST_DIR}/add-catch.cmake" )

set ( DGM_ENGINE_CORE_LIB_VERSION "main" )
set ( CXXOPTS_VERSION "v3.3.1" )
set ( FSM_LIB_VERSION "main" )
set ( CATCH2_VERSION "v3.8.0" )

CPMAddPackage("gh:nerudaj/dgm-engine-core-lib#${DGM_ENGINE_CORE_LIB_VERSION}")
CPMAddPackage("gh:jarro2783/cxxopts#${CXXOPTS_VERSION}")

CPMAddPackage("gh:nerudaj/fsm-lib#${FSM_LIB_VERSION}")
AddCatch( "${CATCH2_VERSION}" )
