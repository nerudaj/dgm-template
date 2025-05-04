cmake_minimum_required ( VERSION 3.26 )

include ( "cmake/vars.cmake" )
include ( "cmake/cpp-init.cmake" )

cpp_init()
get_version_from_git (
    PROJECT_VERSION_VARIABLE GIT_PROJECT_VERSION
    FULL_VERSION_VARIABLE FULL_PROJECT_VERSION
)

project ( ${THE_PROJECT_NAME} VERSION ${GIT_PROJECT_VERSION} )

option ( BUILD_TESTS "Build unit testing target" ON )
option ( USE_NSIS "Use NSIS for packaging" OFF )

set ( OUTPUT_FILE_NAME "${THE_PROJECT_NAME}-v${CMAKE_PROJECT_VERSION}" )

if ( ${CMAKE_BUILD_SYSTEM} STREQUAL "Android" )
    message ( "Configuring for Android build" )

    set ( CURRENT_USER_NAME $ENV{USERNAME} )

    message ( "Detected current user: ${CURRENT_USER_NAME}" )

    make_directory ( "${CMAKE_CURRENT_BINARY_DIR}/app/src/main" )

    file (
        COPY
            "${CMAKE_CURRENT_SOURCE_DIR}/android/gradle/gradle"
            "${CMAKE_CURRENT_SOURCE_DIR}/android/gradle/build.gradle.kts"
            "${CMAKE_CURRENT_SOURCE_DIR}/android/gradle/gradle.properties"
            "${CMAKE_CURRENT_SOURCE_DIR}/android/gradle/gradlew"
            "${CMAKE_CURRENT_SOURCE_DIR}/android/gradle/gradlew.bat"
            "${CMAKE_CURRENT_SOURCE_DIR}/android/gradle/settings.gradle.kts"
        DESTINATION
            ${CMAKE_CURRENT_BINARY_DIR}
    )
    
    file (
        COPY
            "${CMAKE_CURRENT_SOURCE_DIR}/android/res"
        DESTINATION
            "${CMAKE_CURRENT_BINARY_DIR}/app/src/main"
    )

    configure_file (
        "${CMAKE_CURRENT_SOURCE_DIR}/android/infiles/local.properties.in"
        "${CMAKE_CURRENT_BINARY_DIR}/local.properties"
    )

    configure_file (
        "${CMAKE_CURRENT_SOURCE_DIR}/android/infiles/build.gradle.kts.in"
        "${CMAKE_CURRENT_BINARY_DIR}/app/build.gradle.kts"
    )
    
    configure_file (
        "${CMAKE_CURRENT_SOURCE_DIR}/android/infiles/proguard-rules.pro.in"
        "${CMAKE_CURRENT_BINARY_DIR}/app/proguard-rules.pro"
    )

    configure_file (
        "${CMAKE_CURRENT_SOURCE_DIR}/android/infiles/AndroidManifest.xml.in"
        "${CMAKE_CURRENT_BINARY_DIR}/app/src/main/AndroidManifest.xml"
    )
    
    install (
        FILES
            "${CMAKE_CURRENT_BINARY_DIR}/app/build/outputs/apk/release/${OUTPUT_FILE_NAME}.apk"
            "${CMAKE_CURRENT_BINARY_DIR}/app/build/outputs/apk/release/output-metadata.json"
        DESTINATION
            "."
    )
    
    message ("Use the following command to build the APK: gradlew build" )
else ()
    message ("Configuring for Windows build")

    set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Compiled" )

    include ( "cmake/dependencies.cmake" )

    add_subdirectory ( "lib" )
    add_subdirectory ( "bin-windows" )

    if ( ${BUILD_TESTS} )
        enable_testing()
        add_subdirectory ( "tests" )
    endif ()
endif ()

set ( CPACK_GENERATOR "ZIP" )
set ( CPACK_PACKAGE_FILE_NAME "${OUTPUT_FILE_NAME}" )

include ( CPack )
