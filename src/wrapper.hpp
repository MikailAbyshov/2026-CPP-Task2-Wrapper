#pragma once

#include <functional>
#include <map>
#include <string>

class Wrapper {
public:
    using ArgMap = std::map<std::string, std::string>;
    using Callable = std::function<std::string(const ArgMap&)>;

    Wrapper(Callable callable, ArgMap defaults);

    [[nodiscard]] std::string invoke(const ArgMap& overrides) const;
    [[nodiscard]] const ArgMap& defaults() const noexcept;

private:
    Callable callable_;
    ArgMap defaults_;
};