set ( THE_PROJECT_NAME "Template" )
set ( LIB_TARGET_NAME "game-lib" )
set ( TEST_TARGET_NAME "unit-tests" )

string ( TOLOWER "${THE_PROJECT_NAME}" PROJECT_NAME_LOWERCASE )

# C++ vars
set ( USE_SFML_TGUI_STATIC_LINKAGE OFF )

# Installer
set ( INSTALLER_ABOUT_URL "https://mygame.org/" )

# Android vars
set ( ANDROID_ORG "org.nerudaj.${PROJECT_NAME_LOWERCASE}" )
set ( ANDROID_NATIVE_LIB_NAME "cppcore" )
set ( ANDROID_ARCH_ABI "arm64-v8a" )
set ( ANDROID_NDK_VERSION "29.0.14206865" )
set ( ANDROID_MIN_SDK "27" ) # Android 8.1 and newer (2017 onwards)
set ( ANDROID_TARGET_SDK "33" )
set ( ANDROID_ENFORCED_ORIENTATION "landscape" ) # landscape | portrait

## shortEdges mean that the app will render into camera cutout area
set ( ANDROID_WINDOW_LAYOUT_IN_DISPLAY_CUTOUT_MODE "never" ) # shortEdges | never
