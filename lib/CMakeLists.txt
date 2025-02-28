cmake_minimum_required ( VERSION 3.26 )

configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/include/misc/CMakeVars.hpp.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/misc/CMakeVars.hpp"
)

make_static_library ( ${LIB_TARGET_NAME}
    DEPS
        nlohmann_json::nlohmann_json
        dgm::dgm-lib
        fsm::fsm-lib
        TGUI::TGUI
)
