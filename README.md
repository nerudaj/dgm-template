# dgm project template

## Table of Contents

- [Project structure](#project-structure)
- [Customizing template](#customizing-template)
- [Propagating CMake variables into native code](#propagating-cmake-variables-into-native-code)
- [Building for Windows](#building-for-windows)
  - [Dependencies](#dependencies)
  - [Setup](#setup)
- [Building for Android](#building-for-android)
  - [Dependencies](#dependencies-1)
  - [Setup](#setup-1)

## Project structure

 * `assets` - All runtime assets that will be packaged and distributed with the game go here. If you respect the structure of subfolders, your assets will be autoloaded into `dgm::ResourceManager` on start of the app.
 * `bin-android` - Contains entire project structure for Android Studio to work with. The only thing you should meddle with in there is `Main.cpp` in `cppcore` folder. Nothing else doesn't need touching.
 * `bin-windows` - Contains `Main.cpp` for Windows app.
 * `cmake` - Contains utility CMake files.
 * `lib` - Contains the entire code of the application.
 * `tests` - Contains unit testing source codes.

### Customizing template

Start with `cmake/vars.cmake` file. Change the project name variable (affects name of the Windows solution, name of the app and name of the build target in the solution).

You can toy with other project names and compilation flags, but the default should work well.

If you plan to deploy on Android, change the value of `ANDROID_ORG` as well.

### Propagating CMake variables into native code

If you need to reference certain CMake variable values in native code, add them to `lib/misc/CMakeVars.hpp.in`. During configure, this file is configured into `lib/misc/CMakeVars.hpp` and you can include it easily in code through `#include <misc/CMakeVars.hpp>`.

## Building for Windows

### Dependencies

* Visual Studio 2022 (v17.12+) with platform toolset v143
* CMake v3.28.1+
* Optional: NSIS v3+ (for packaging)

### Setup

Configure cmake:

```sh
mkdir _build
cd _build

# of USE_NSIS=ON, configures cpack to use NSIS instead of zip (generates installer)
cmake [-D USE_NSIS=ON] ..
```

This will generate a `<project-name>.sln` file inside `_build`. You can open it in Visual Studio and work from there. When you use `-D USE_NSIS=ON`, then CPack would use NSIS (must be installed) instead of Zip for packaging.

Or you can build the whole thing from the command line:

```sh
cmake --build . --config Release
ctest -C Release
cpack
```

## Building for Android

## Dependencies

* Java SDK 11
* Android NDK
* CMake v3.28.1+
* Gradle is fetched automatically through gradlew

## Setup

Configure cmake:

```sh
mkdir _build
cd _build
cmake -D BUILD_ANDROID=ON ..
```

This will generate `bin-android/local.properties`, `bin-android/app/build.gradle.kts` and `bin-android/app/src/main/AppManifest.xml`. After that you can open the `bin-android` folder as a project in Android Studio and continue from there.

Or you can build the whole thing from the command-line (inside `bin-android`):

```sh
gradlew build
```
