#pragma once

#include <DGM/classes/Compatibility.hpp>

#ifdef ANDROID
#include <fmt/core.h>
#endif

#ifdef ANDROID
namespace uni = fmt;
#else
namespace uni = std;
#endif
