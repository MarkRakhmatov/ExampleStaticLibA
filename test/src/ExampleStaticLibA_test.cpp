#include <boost/ut.hpp>

#include <ExampleStaticLibA/ExampleStaticLibA.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <exception>

using namespace boost::ut;

void tests() {
  "get string"_test = [] {
    expect(!libA::getString().empty());
    expect(libA::getString() == std::string("cpp static lib example"));
  };

  "factorial"_test = [] {
    expect(libA::factorial(0) == 1_i);
    expect(libA::factorial(1) == 1_i);
    expect(libA::factorial(2) == 2_i);
    expect(libA::factorial(12) == 479001600_i);
    expect(libA::factorial(13) == -1_i);
  };

  "factorial_constexpr"_test = [] {
    static_assert(libA::factorialConstexpr(0) == 1_i);
    static_assert(libA::factorialConstexpr(1) == 1_i);
    static_assert(libA::factorialConstexpr(2) == 2_i);
  };
}

int main(int argc, const char** argv) {
  try {
    boost::ut::detail::cfg::parse_arg_with_fallback(argc, argv);
    tests();
  } catch (const std::exception& ex) {
    std::cout << "exception: "<< ex.what();
    return EXIT_FAILURE;
  }
  catch (...) {
    std::cout <<"unknown exception";
    return EXIT_FAILURE;
  }
}
