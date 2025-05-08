set ( THE_PROJECT_NAME "Template" )
set ( LIB_TARGET_NAME "game-lib" )
set ( TEST_TARGET_NAME "unit-tests" )

# C++ vars
set ( USE_SFML_TGUI_STATIC_LINKAGE OFF )
set ( USE_PREBUILT_LIBRARIES OFF )

# Android vars
set ( ANDROID_ORG "org.nerudaj.template" )
set ( ANDROID_NATIVE_LIB_NAME "cppcore" )
set ( ANDROID_ARCH_ABI "arm64-v8a" )
set ( ANDROID_NDK_VERSION "26.1.10909125" )
set ( ANDROID_MIN_SDK "21" )
set ( ANDROID_TARGET_SDK "33" )
set ( ANDROID_ENFORCED_ORIENTATION "landscape" ) # landscape | portrait