#pragma once

#include <list>
#include "Mark.hpp"

namespace ImGuiGradient {

/// Used to identify a Mark.
class MarkId {
public:
    explicit MarkId(const Mark* ptr)
        : _ptr{ptr}
    {}
    explicit MarkId(const Mark& ref)
        : _ptr{&ref}
    {}
    explicit MarkId(const std::list<Mark>::const_iterator iterator)
        : _ptr{&*iterator}
    {}

    void reset() { _ptr = nullptr; }

    friend auto operator==(const MarkId& a, const MarkId& b) -> bool { return a._ptr == b._ptr; };
    friend auto operator!=(const MarkId& a, const MarkId& b) -> bool { return !(a == b); };

private:
    friend class Gradient;
    template<typename GradientT>
    auto find(GradientT&& gradient) const
    {
        const auto it = std::find_if(gradient._marks.begin(), gradient._marks.end(), [&](const Mark& mark) {
            return &mark == _ptr;
        });
        return it != gradient._marks.end()
                   ? &*it
                   : nullptr;
    }

private:
    const Mark* _ptr{};
};

} // namespace ImGuiGradient