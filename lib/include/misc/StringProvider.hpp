#pragma once

#include "enums/Language.hpp"
#include "types/StringTypes.hpp"
#include <string>
#include <vector>
#include <utility>

class [[nodiscard]] StringProvider final
{
public:
    StringProvider(Language primary);

    StringProvider(StringProvider&&) = delete;
    StringProvider(const StringProvider&) = delete;

public:
    constexpr void changeLanguage(Language newLang) noexcept
    {
        current = newLang;
    }

    constexpr const CharType* getString(StringId id) const noexcept
    {
        return strings[std::to_underlying(current)][std::to_underlying(id)]
            .data();
    }

private:
    Language current = Language {};
    std::vector<std::vector<std::string_view>> strings;
};
