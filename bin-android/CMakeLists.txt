cmake_minimum_required( VERSION 3.28 )

set ( CURRENT_USER_NAME $ENV{USERNAME} )

message ( "Detected current user: ${CURRENT_USER_NAME}" )

configure_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/local.properties.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/local.properties"
)

configure_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/app/build.gradle.kts.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/build.gradle.kts"
)

configure_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/AndroidManifest.xml.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/AndroidManifest.xml"
)

add_custom_target( android-build ALL 
    COMMAND "gradlew assemble"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/AndroidManifest.xml" "${CMAKE_CURRENT_SOURCE_DIR}/app/build.gradle.kts"
)

