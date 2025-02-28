cmake_minimum_required( VERSION 3.28 )

# TODO: fix these
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/app/main/src/AppManifest.xml.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/app/main/src/AppManifest.xml"
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/app/main/gradle.build.kts.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/app/main/gradle.build.kts"
)

add_custom_target( android-build ALL 
    COMMAND "gradlew assemble"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/app/main/src/AppManifest.xml" "${CMAKE_CURRENT_SOURCE_DIR}/app/main/gradle.build.kts"
)

# TODO: install rules
