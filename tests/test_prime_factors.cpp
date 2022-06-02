#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <vector>
#include <tuple>
#include <numeric>
#include <catch2/generators/catch_generators_all.hpp>

std::vector<std::size_t> prime_factors(std::size_t number) {
    std::vector<std::size_t> factors;
    const std::size_t max_iteration = (std::size_t) std::ceil(std::sqrt(number)) + 1;
    factors.reserve(max_iteration);
    while (number % 2 == 0) {
        number /= 2;
        factors.emplace_back(2);
    }
    for (size_t i = 3; i <= max_iteration; i += 2) {
        while (number % i == 0) {
            number /= i;
            factors.emplace_back(i);
        }
    }
    if (number != 1) {
        factors.emplace_back(number);
    }
    factors.resize(factors.size());
    return factors;
}

std::tuple<std::size_t, std::size_t> make_rectangle_helper(const std::vector<std::size_t> &factors) {
    std::size_t half_size = factors.size() / 2 + (factors.size() % 2 == 1);
    std::size_t dim1 = std::reduce(factors.begin(), factors.begin() + (std::ptrdiff_t) half_size, 1,
                                   [](auto left, auto right) { return left * right; });
    std::size_t dim2 = std::reduce(factors.begin() + (std::ptrdiff_t) half_size, factors.end(), 1,
                                   [](auto left, auto right) { return left * right; });
    return {dim1, dim2};
}

auto get_dimenstions(std::size_t area) {
    auto factors = prime_factors(area);
    return make_rectangle_helper(factors);
}


TEST_CASE("PrimeFactors") {
    CHECK(prime_factors(2) == std::vector<size_t>{2});
    CHECK(prime_factors(3) == std::vector<size_t>{3});
    CHECK(prime_factors(5) == std::vector<size_t>{5});
    CHECK(prime_factors(7) == std::vector<size_t>{7});
    CHECK(prime_factors(9) == std::vector<size_t>{3, 3});
    CHECK(prime_factors(15) == std::vector<size_t>{3, 5});
    CHECK(prime_factors(1).empty());
    CHECK(prime_factors(105) == std::vector<size_t>{3, 5, 7});
    CHECK(prime_factors(4) == std::vector<size_t>{2, 2});
    CHECK(prime_factors(12) == std::vector<size_t>{2, 2, 3});

}

TEST_CASE("BuildRectangle") {
    CHECK(get_dimenstions(15) == std::tuple<std::size_t, std::size_t>{3, 5});
    CHECK(get_dimenstions(10) == std::tuple<std::size_t, std::size_t>{2, 5});
    CHECK(get_dimenstions(5) == std::tuple<std::size_t, std::size_t>{5, 1});
    CHECK(get_dimenstions(105) == std::tuple<std::size_t, std::size_t>{15, 7});
    CHECK(get_dimenstions(1407) == std::tuple<std::size_t, std::size_t>{21, 67});

}
