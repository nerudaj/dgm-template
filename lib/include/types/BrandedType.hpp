#pragma once

template<class T, class Parameter>
class BrandedType
{
public:
    template<class = std::enable_if<std::is_default_constructible_v<T>>>
    BrandedType() : value(T {})
    {
    }

    explicit constexpr BrandedType(const T& value) : value(value) {}

    explicit constexpr BrandedType(T&& value) : value(std::move(value)) {}

    constexpr auto&& get(this auto&& self)
    {
        return self.value;
    }

private:
    T value;
};
