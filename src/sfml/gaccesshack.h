#ifndef GACCESSHACK_H
#define GACCESSHACK_H

// https://www.reddit.com/r/codenuggets/comments/30ymr1/c_dirty_hack_access_to_protected_members_without/
// http://bloglitb.blogspot.hk/2011/12/access-to-private-members-safer.html

/*
Usage:

class A {
    int a = 42;
    void print() {
        std::cout << "A::a: " << a << '\n';
    }
};

ENABLE_ACCESS(a, ::A, a, int);
ENABLE_ACCESS(print, ::A, print, void());

int main() {
    A x;
    // directly access private data (prints "42")
    std::cout << ACCESS(x, a) << '\n';

    // directly set private data
    ACCESS(x, a) = 100;

    // call private member function
    ACCESS(x, print)();
}

*/

namespace dirty_hacks {
template <typename Tag, typename Tag::type M>
struct GAccessHackRobber {
    friend typename Tag::type get(Tag) {
        return M;
    }
};

template <typename T, typename C, typename M>
struct GAccessHackTagBase {
    using type = M C::*;
    friend type get(T);
};
} // namespace dirty_hacks

#define GINCU_ENABLE_ACCESS_HACK(tag_name, class_name, member_name, member_type)     \
    namespace dirty_hacks {                                               \
        struct tag_name : GAccessHackTagBase<tag_name, class_name, member_type> {}; \
        template struct GAccessHackRobber<tag_name, &class_name::member_name>;          \
    } // namespace dirty_hacks

#define GINCU_ACCESS_HACK(object, tag_name) ((object).*get(::dirty_hacks::tag_name()))


#endif
