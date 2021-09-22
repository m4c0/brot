#pragma once

#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/str.hpp"
#include "m4c0/parser/tokeniser.hpp"

#include <concepts>
#include <cstdlib>
#include <iostream>
#include <type_traits>

static std::ostream & operator<<(std::ostream & o, m4c0::parser::input_t val) {
  return o << std::string(val.begin(), val.end());
}
template<typename T>
static std::ostream & operator<<(std::ostream & o, m4c0::parser::token<T> val) {
  return o << val.value;
}

namespace brot::parser {
  using nil = m4c0::parser::nil;

  namespace token_names {
    struct spec {};
    struct param_name {};
    struct param_value {};
  };
  namespace tokens {
    using spec = m4c0::parser::token<token_names::spec>;
    using param_name = m4c0::parser::token<token_names::param_name>;
    using param_value = m4c0::parser::token<token_names::param_value>;
  }

  namespace impl {
    using namespace m4c0::parser;

    static constexpr const auto spaces = many(skip(match_any_of(" \t\r\n")));

    static constexpr const auto lparen = skip(match('('));
    static constexpr const auto rparen = skip(match(')'));
    static constexpr const auto colon = skip(match(':'));
    static constexpr const auto param_chars = many(skip(match_none_of("\r\n():")));
    static constexpr const auto token_chars = at_least_one(skip(match_none_of(" \t\r\n():")));

    template<typename T>
    static constexpr const auto token = tokenise<T>(token_chars);
    static constexpr const auto param_token = tokenise<token_names::param_value>(param_chars);

    static constexpr const auto spec_name = token<token_names::spec> + colon;
    static constexpr const auto param_name = token<token_names::param_name>;
    static constexpr const auto param_value = lparen & param_token + rparen + spaces;
  }

  template<typename P>
  concept valid_processor = requires(P p) {
    P();
    (p.begin_spec())(std::declval<tokens::spec>());
    (p.add_parameter())(std::declval<tokens::param_name>(), std::declval<tokens::param_value>());
    { p.finish() } -> std::same_as<bool>;
  };

  template<typename P>
  requires valid_processor<P>
  static auto parse(std::istream & in) noexcept {
    P p {};

    const auto spec_name = impl::spec_name & p.begin_spec();
    const auto param = combine(impl::param_name, impl::param_value, p.add_parameter());
    const auto component = skip(spec_name & impl::spaces & at_least_one(param));
    const auto file = impl::spaces & many(component) & m4c0::parser::eof() | "Invalid statement";

    std::string str { std::istreambuf_iterator<char> { in }, {} };
    return file({ str.data(), str.length() }) % [p = &p](auto n, auto rem) {
      if constexpr (!std::is_same_v<std::decay_t<decltype(n)>, m4c0::parser::input_t>) {
        return p->finish() ? EXIT_SUCCESS : EXIT_FAILURE;
      } else {
        using namespace m4c0::parser;
        struct line {};
        constexpr const auto line_parser = tokenise<line>(many(skip(match_none_of("\n"))));
        line_parser(rem) % [n](auto line) {
          std::cerr << n << " around this:\n    " << line << "\n";
        };
        return EXIT_FAILURE;
      }
    };
  }
}
