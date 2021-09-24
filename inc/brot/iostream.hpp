#pragma once

#include "brot/parser.hpp"
#include "m4c0/parser/str.hpp"

#include <iostream>
#include <iterator>
#include <string>

namespace brot::iostream {
  static std::ostream & operator<<(std::ostream & o, m4c0::parser::input_t i) {
    return o.write(i.begin(), i.length());
  }
  template<typename T>
  static std::ostream & operator<<(std::ostream & o, m4c0::parser::token<T> t) {
    return o << t.value;
  }

  static constexpr auto print() noexcept {
    return [](auto n) {
      std::cout << n;
      return n;
    };
  }

  static constexpr auto print_name(auto n) noexcept {
    std::cout << n << ":";
  }
  static constexpr auto print_param(auto n, auto v) noexcept {
    std::cout << n << "(" << v << ")";
  }
}

namespace brot::iostream {
  namespace impl {
    struct end {
      constexpr auto operator()(auto /*v*/, auto /*rem*/) {
        return EXIT_SUCCESS;
      }
      constexpr auto operator()(m4c0::parser::input_t err, auto rem) {
        if (rem.empty()) {
          std::cerr << err << " around EOF\n";
          return EXIT_FAILURE;
        }

        using namespace m4c0::parser;
        struct line {};
        constexpr const auto line_parser = tokenise<line>(many(skip(match_none_of("\n"))));
        line_parser(rem) % [err](auto line) {
          std::cerr << err << " around this:\n    " << line << "\n";
        };
        return EXIT_FAILURE;
      }
    };
  }

  template<typename P>
  requires m4c0::parser::is_parser<P>
  static auto parse_cin(P && p) {
    std::string in { std::istream_iterator<char> { std::cin >> std::noskipws }, {} };
    return p({ in.data(), in.length() }) % impl::end();
  }
}
