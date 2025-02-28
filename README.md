# dgm project template

## Table of Contents

**TODO:** this

## Dependencies

For Windows build, you need these:

* Visual Studio 2022 (v17.12+) with platform toolset v143
* CMake v3.28.1+

All build dependencies are fetched automatically by CMake.

For Android build, you need these:

* Java SDK 11
* Android NDK
* Visual Studio 2022 (v17.12+) with Android build tools
* CMake v3.28.1+
* Gradle is fetched automatically through gradlew

## Setup

To customize the name of the project and various other values, edit `cmake/vars.cmake`.

Most notably, you want to change the value of `THE_PROJECT_NAME`.

**TODO:** Android-related variables

### Propagating CMake variables into native code

If you need to reference certain CMake variable values in native code, add them to `lib/misc/CMakeVars.hpp.in`. During configure, this file is configured into `lib/misc/CMakeVars.hpp` and you can include it easily in code through `#include <misc/CMakeVars.hpp>`.

## Project structure

* `android` - Contains Graddle wrapper and definition of the Android project. Build of Android is managed through CMake.
* `assets` - Folder where you should put ALL game assets - textures, fonts, icons, levels, everything.
* `bin` - Project for Windows executable / Android native library. This one handles the start of the program, instantiation of top-level classes, loading resources, etc.
* `cmake` - Folder for various `.cmake` scripts. Most notably `dependencies.cmake` that handles external dependencies and `vars.cmake` that handles some project-level variables, like project name.
* `lib` - Project for the game engine, all of the game logic, application logic, etc.
* `tests` - Project for writing unit tests.

## How to build

### Windows

Considering you only have Visual Studio 2022 installed (otherwise you need to tell CMake you want to use MSVC through `-G`). In project root directory:

```sh
# Create build folder
mkdir _build
cd _build

# Configure everything, download build dependencies
# Generate MSVC solution file for development
# of USE_NSIS=ON, configures cpack to use NSIS instead of zip (generates installer)
cmake [-D USE_NSIS=ON] ..
cmake --build . --config Release # or Debug; builds everything
ctest -C Release # to run unit tests on previously built configuration
cpack # generates either a zip package or NSIS installer
```

### Android

Works pretty much the same as Windows build, the only difference is CMake option used:

```sh
mkdir _build
cd _build

# Generates project files under `android` so you can open that folder in Android Studio
cmake -D BUILD_ANDROID=ON ..
cmake --build . --config Release
# No unit tests supported in this setup
cpack # generates a zip package containing .apk
```
