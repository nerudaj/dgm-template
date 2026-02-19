[![CI-Windows](https://github.com/nerudaj/dgm-template/actions/workflows/ci-windows.yml/badge.svg?branch=main)](https://github.com/nerudaj/dgm-template/actions/workflows/ci-windows.yml) [![CI-Android](https://github.com/nerudaj/dgm-template/actions/workflows/ci-android.yml/badge.svg?branch=main)](https://github.com/nerudaj/dgm-template/actions/workflows/ci-android.yml)

# dgm project template

## Table of Contents

- [Project structure](#project-structure)
- [Documentation](#documentation)
  - [Customizing template](#customizing-template)
  - [Propagating CMake variables into native code](#propagating-cmake-variables-into-native-code)
- [Building for Windows](#building-for-windows)
  - [Dependencies](#dependencies)
  - [Setup](#setup)
- [Building for Android](#building-for-android)
  - [Dependencies](#dependencies-1)
  - [Setup](#setup-1)
  - [Signing APKs](#signing-apks)
- [Building for Ubuntu](#building-for-ubuntu)
- [Known issues](#known-issues)

## Project structure

 * `assets` - All runtime assets that will be packaged and distributed with the game go here. If you respect the structure of subfolders, your assets will be autoloaded into `dgm::ResourceManager` on start of the app.
 * `assets-private` - Assets that should be under version control, but not directly installed with the game, such as application icon or project files for Gimp or similar programs.
 * `bin-android` - Contains the Android entry point (`Main.cpp`) and CMake configuration for Android builds. Nothing else in this folder needs touching.
 * `bin-windows` - Contains `Main.cpp` for Windows app.
 * `cmake` - Contains utility CMake files.
 * `lib` - Contains the entire code of the application.
 * `tests` - Contains unit testing source codes.

## Documentation

For additional guides (application icons, APK signing, UI), see the [documentation index](docs/Readme.md).

### Customizing template

Start with `cmake/vars.cmake` file. Change the project name variable (affects name of the Windows solution, name of the app and name of the build target in the solution).

You can toy with other project names and compilation flags, but the default should work well.

If you plan to deploy on Android, change the value of `ANDROID_ORG` as well.

### Propagating CMake variables into native code

If you need to reference certain CMake variable values in native code, add them to `lib/include/misc/CMakeVars.hpp.in`. During configuration, this file is generated as `lib/include/misc/CMakeVars.hpp` and you can include it in code via `#include <misc/CMakeVars.hpp>`.

## Building for Windows

### Dependencies

* Visual Studio 2022 (v17.12+) with platform toolset v143
* CMake v3.28.1+
* Optional: NSIS v3+ (for packaging)

### Setup

Configure cmake:

```sh
# If USE_NSIS=ON, configures CPack to use NSIS instead of ZIP (generates installer)
cmake -B _build . [-D USE_NSIS=ON]
```

This will generate a `<project-name>.sln` file inside `_build`. You can open it in Visual Studio and work from there. When you use `-D USE_NSIS=ON`, CPack will use NSIS (must be installed) instead of ZIP for packaging.

Or you can build the whole thing from the command line:

```sh
cmake --build _build --config Release
ctest --test-dir _build -C Release
cpack --config _build/CPackConfig.cmake
```

## Building for Android

### Dependencies

* Java SDK 11
* Android NDK
* CMake v3.28.1+
* Gradle is fetched automatically through gradlew

### Setup

Configure cmake:

```sh
cmake -B _build . -D BUILD_ANDROI=ON
```

After that you can open the `_build` folder as a project in Android Studio and continue from there. Or you can directly invoke Gradle and build from the command line:

```sh
gradlew build
cpack
```

### Signing APKs

The `Release-Android` pipeline is capable of automatically signing the release APKs for you, provided you have appropriate secrets defined for this repo. Read [this guide](docs/ApkSigning.md) for more details.

## Building for Ubuntu

Unlike on Windows, SFML doesn't automatically fetch its dependencies on Linux. You need to install the following packages first:

```sh
apt install libxrandr-dev libxcursor-dev libxi-dev libudev-dev libfreetype-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libfreetype-dev libharfbuzz-dev
```

The supported compiler is Clang 18 (and presumably anything newer will work). However, Clang uses libc++ implementation from GCC which has some troubles with std::ranges, so you also need to install Clang's implementation of libc++ and link that.

First, make sure you have package `libc++-dev` installed, then select it during configuration:

```sh
cmake -B _build . -D CMAKE_C_COMPILER=clang-18 -D CMAKE_CXX_COMPILER=clang++-18 -D CMAKE_CXX_FLAGS=-stdlib=libc++
```

## Known issues

* TGUI seems to incorrectly compute offsets on Android. For example textured menu backgrounds are cropped at 50% height. Positions of containers in Options menu are shifted to right, which doesn't happen on Windows, etc.
* Graphic assets bigger than 1024 px in a single dimension will make unit tests in CI fail, since there are some sanity tests that are loading resources and the build agents don't have enough VRAM.
* On Ubuntu, font/container sizes are hardcoded values, instead of being polled from system properties like on Android or Windows. PRs implementing this are welcome.
* On Ubuntu, current working directory is used for storing settings/save data. It should point to some temp directory. PRs implementing this are welcome.
