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
    auto get_ptr() const -> const Mark* { return _ptr; }

private:
    const Mark* _ptr{};
};

} // namespace ImGuiGradient