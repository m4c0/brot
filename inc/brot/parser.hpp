#pragma once

#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/constants.hpp"
#include "m4c0/parser/str.hpp"
#include "m4c0/parser/tokeniser.hpp"

namespace brot::parser::token_ids {
  struct name;
  struct value;
}
namespace brot::parser::tokens {
  using name = m4c0::parser::token<token_ids::name>;
  using value = m4c0::parser::token<token_ids::value>;
}

namespace brot::parser::impl {
  using namespace m4c0::parser;

  static constexpr const auto spaces = many(skip(match_any_of(" \t\r\n")));

  static constexpr const auto lparen = skip(match('('));
  static constexpr const auto rparen = skip(match(')'));
  static constexpr const auto colon = skip(match(':'));
  static constexpr const auto name_chars = at_least_one(skip(match_none_of(" \t\r\n():")));
  static constexpr const auto value_chars = many(skip(match_none_of("\r\n():")));

  static constexpr const auto name = tokenise<token_ids::name>(name_chars);
  static constexpr const auto value = tokenise<token_ids::value>(value_chars);

  static constexpr const auto eof = m4c0::parser::eof() | "Invalid component";

  template<typename P>
  requires is_parser<P>
  static constexpr auto parse_or_fail(P && p, input_t msg) {
    return p | fail<type_of_t<P>>(msg);
  }
}

namespace brot::parser {
  static constexpr const auto name = impl::name;
  static constexpr const auto value = impl::value;

  template<typename P>
  requires impl::is_parser<P>
  static constexpr auto compo_name(P && name_p) noexcept {
    return impl::parse_or_fail(name_p + impl::colon + impl::spaces, "Invalid component name");
  }
  template<typename PV>
  requires impl::is_parser<PV>
  static constexpr auto parameter(impl::input_t name, PV && value_p) noexcept {
    return impl::parse_or_fail(
        impl::match(name) & impl::lparen & value_p + impl::rparen + impl::spaces,
        "Invalid parameter");
  }
  template<typename PN, typename PV>
  requires impl::is_parser<PN> && impl::is_parser<PV>
  static constexpr auto parameter(PN && name_p, PV && value_p) noexcept {
    return impl::parse_or_fail(name_p + impl::lparen + value_p + impl::rparen + impl::spaces, "Invalid parameter");
  }
  static constexpr auto parameter() noexcept {
    return parameter(skip(name), skip(value));
  }

  template<typename PN, typename PV>
  requires impl::is_parser<PN> && impl::is_parser<PV>
  static constexpr auto component(PN && compo_name_p, PV && param_p) noexcept {
    return compo_name_p + param_p << param_p;
  }

  template<typename P0, typename PC>
  requires impl::is_parser<P0> && impl::is_parser<PC>
  static constexpr auto file(P0 && init_p, PC && compo_p) noexcept {
    return (init_p + impl::spaces + compo_p << compo_p) + impl::eof;
  }
}
