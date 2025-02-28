#pragma once

#include "enums/StringId.hpp"
#include <map>
#include <string>

using CharType = char;
using StringView = std::basic_string_view<CharType>;
using Localization = std::map<StringId, StringView>;
