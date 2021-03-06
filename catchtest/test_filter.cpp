#include <filter.hpp>

#include "helpers.hpp"

#include <vector>
#include <string>
#include <iterator>

#include "catch.hpp"

using iter::filter;

using Vec = const std::vector<int>;

namespace {
    bool less_than_five(int i) {
        return i < 5;
    }

    class LessThanValue {
        private:
            int compare_val;

        public:
            LessThanValue(int v) : compare_val(v) { }

            bool operator() (int i) {
                return i < this->compare_val;
            }
    };
}

TEST_CASE("filter: handles different functor types", "[filter]") {
    Vec ns = {1,2, 5,6, 3,1, 7, -1, 5};
    Vec vc = {1,2,3,1,-1};
    SECTION("with function pointer") {
        auto f = filter(less_than_five, ns);
        Vec v(std::begin(f), std::end(f));
        REQUIRE( v == vc );
    }

    SECTION("with callable object") {
        auto f = filter(LessThanValue{5}, ns);
        Vec v(std::begin(f), std::end(f));
        REQUIRE( v == vc );
    }

    SECTION("with lambda") {
        auto ltf = [](int i) {return i < 5;};
        auto f = filter(ltf, ns);
        Vec v(std::begin(f), std::end(f));
        REQUIRE( v == vc );
    }
}

TEST_CASE("filter: using identity", "[filter]") {
    Vec ns{0, 1, 2, 0, 3, 0, 0, 0, 4, 5, 0};
    auto f = filter(ns);
    Vec v(std::begin(f), std::end(f));

    Vec vc = {1,2,3,4,5};
    REQUIRE( v == vc );
}

TEST_CASE("filter: binds to lvalues, moves rvales", "[filter]") {
    itertest::BasicIterable<int> bi{1,2,3,4};

    SECTION("one-arg binds to lvalues") {
        filter(bi);
        REQUIRE_FALSE(bi.was_moved_from());
    }

    SECTION("two-arg binds to lvalues") {
        filter(less_than_five, bi);
        REQUIRE_FALSE(bi.was_moved_from());
    }

    SECTION("one-arg moves rvalues") {
        filter(std::move(bi));
        REQUIRE(bi.was_moved_from());
    }

    SECTION("two-arg moves rvalues") {
        filter(less_than_five, std::move(bi));
        REQUIRE(bi.was_moved_from());
    }
}


TEST_CASE("filter: all elements fail predicate", "[filter]") {
    Vec ns{10,20,30,40,50};
    auto f = filter(less_than_five, ns);

    REQUIRE( std::begin(f) == std::end(f) );
}

TEST_CASE("filter: doesn't move or copy elements of iterable", "[filter]") {
    constexpr itertest::SolidInt arr[] = {{1}, {0}, {2}};
    for (auto&& i : filter(
                [](const itertest::SolidInt& si) {return si.getint();},arr)) {
        (void)i;
    }
}
