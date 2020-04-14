#include "../src/multi_string.hpp"
#include <cassert>
#include <string_view>

constexpr std::string_view hello = "hello ";
constexpr std::string_view world = "world";

template<class Str>
void test_methods(Str const& s) {
    assert(s[0] == hello);
    assert(s[1] == world);

    assert(s.size() == 2);

    assert(s.str_size(0) == hello.size());
    assert(s.str_size(1) == world.size());

    assert(s.total_str_sizes() == (hello.size() + world.size()));

    auto it = s.begin();
    assert(it != s.end());
    assert(*it++ == hello);
    assert(it != s.end());
    assert(*it++ == world);
    assert(it == s.end());
}

template<class Str>
void test() {
    Str s(hello, world);
    test_methods(s);    

    Str copy = s;
    test_methods(copy);

    Str move = std::move(s);
    test_methods(move);
}


int main() {
    test<stores_ptrs::multi_string>();
    test<stores_sizes::multi_string>();
}