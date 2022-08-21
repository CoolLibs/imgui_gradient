#pragma once

#include <algorithm>
#include <list>
#include "Mark.hpp"

namespace ImGG {

namespace internal {
// Thanks to https://stackoverflow.com/a/34143224
template<class T, class U>
struct transfer_const {
    using type = typename std::remove_const<U>::type*;
};
template<class T, class U>
struct transfer_const<const T&, U> {
    using type = const U*;
};
} // namespace internal

/// Used to identify a Mark.
class MarkId {
public:
    MarkId() = default;
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
    auto find(GradientT&& gradient) const -> typename internal::transfer_const<GradientT, Mark>::type // Returns a `const Mark*` if GradientT is const and a mutable `Mark*` otherwise.
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

} // namespace ImGG