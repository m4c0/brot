#pragma once

#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/str.hpp"

#include <cstdlib>
#include <iostream>
#include <type_traits>

namespace brot::parser {
  using input_t = m4c0::parser::input_t;

  template<typename A, typename B>
  concept is_composable_with = std::is_invocable_v<std::plus<>, A, B>;

  template<typename Tp, typename InnerTp>
  concept is_list_of = std::is_constructible_v<Tp> && is_composable_with<const Tp, const InnerTp>;

  template<typename Tp>
  concept is_statement = std::is_constructible_v<Tp, input_t, input_t>;

  template<typename Tp, typename SLTp>
  concept is_spec = std::is_constructible_v<Tp, input_t, SLTp>;

  // Just wait until Apple's clang support `concept a = requires` or until clang-format do a better job formatting these

  template<typename PTp, typename FTp>
  concept can_print = std::is_invocable_r_v<bool, PTp, FTp>;

  template<typename Tp>
  concept valid_config =                                                 //
      is_statement<typename Tp::statement> &&                            //
      is_list_of<typename Tp::statement_list, typename Tp::statement> && //
      is_spec<typename Tp::spec, typename Tp::statement_list> &&         //
      is_list_of<typename Tp::file, typename Tp::spec> &&                //
      can_print<typename Tp::print, typename Tp::file> &&                //
      true;

  namespace impl {
    using namespace m4c0::parser;

    static constexpr const auto spaces = many(skip(match_any_of(" \t\r\n")));

    static constexpr const auto lparen = skip(match('('));
    static constexpr const auto rparen = skip(match(')'));
    static constexpr const auto colon = skip(match(':'));
    static constexpr const auto param_chars = many(skip(match_none_of("\r\n():")));
    static constexpr const auto token_chars = at_least_one(skip(match_none_of(" \t\r\n():")));

    static constexpr const auto token = tokenise(token_chars);

    static constexpr const auto params = lparen & tokenise(param_chars) + rparen + spaces;

    template<typename Tp>
    static constexpr const auto statement = spaces & combine(token, params, [](auto name, auto param) {
      return Tp { name, param };
    });
    template<typename LTp, typename STp>
    static constexpr const auto statement_list = spaces & at_least_one(statement<STp>, LTp {}) + spaces;

    static constexpr const auto spec_preamble = token + colon;

    template<typename SpecTp, typename LTp, typename STp>
    static constexpr const auto spec = combine(spec_preamble, statement_list<LTp, STp>, [](auto name, auto stmts) {
      return SpecTp { name, stmts };
    });

    template<typename FTp, typename Printer>
    struct print {
      int operator()(FTp f, brot::parser::input_t /*rem*/) {
        return Printer {}(f) ? EXIT_SUCCESS : EXIT_FAILURE;
      }
      int operator()(brot::parser::input_t n, brot::parser::input_t rem) {
        using namespace m4c0::parser;
        constexpr const auto line_parser = tokenise(many(skip(match_none_of("\n"))));
        line_parser(rem) % [n](auto line) {
          const auto err = std::string(n.begin(), n.end());
          const auto ctx = std::string(line.begin(), line.end());
          std::cerr << err << " around this:\n    " << ctx << "\n";
        };

        return EXIT_FAILURE;
      }
    };
  }

  template<typename Config>
  requires valid_config<Config>
  static auto parse(std::istream & in) noexcept {
    using file_t = typename Config::file;
    using print_t = typename Config::print;
    using spec_t = typename Config::spec;
    using stmt_t = typename Config::statement;
    using stmt_list_t = typename Config::statement_list;

    static constexpr const auto spec = impl::spec<spec_t, stmt_list_t, stmt_t>;

    static constexpr const auto file = many(spec, file_t {}) + m4c0::parser::eof() | "Invalid statement";

    std::string str { std::istreambuf_iterator<char> { in }, {} };
    return file({ str.data(), str.length() }) % impl::print<file_t, print_t> {};
  }
}
