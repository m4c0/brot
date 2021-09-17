#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/str.hpp"

#include <iostream>
#include <type_traits>

template<typename Tp>
concept accepts_token = std::is_constructible_v<Tp, m4c0::parser::input_t>;

template<typename A, typename B>
concept is_composable_with = std::is_invocable_v<std::plus<>, A, B>;

template<typename Tp, typename InnerTp>
concept is_list_of = std::is_constructible_v<Tp> && is_composable_with<const Tp, const InnerTp>;

template<typename Tp, typename ParamTp>
concept is_statement = accepts_token<Tp> && is_composable_with<const Tp, ParamTp>;

// Just wait until Apple's clang support `concept a = requires` or until clang-format do a better job formatting these

template<typename PTp, typename FTp>
concept can_print =                                                           //
    std::is_invocable_v<PTp, FTp, m4c0::parser::input_t> &&                   //
    std::is_invocable_v<PTp, m4c0::parser::input_t, m4c0::parser::input_t> && //
    true;

template<typename Tp>
concept valid_config =                                                    //
    accepts_token<typename Tp::id> &&                                     //
    accepts_token<typename Tp::param> &&                                  //
    is_list_of<typename Tp::param_list, typename Tp::param> &&            //
    is_statement<typename Tp::statement, typename Tp::param_list> &&      //
    is_list_of<typename Tp::statement_list, typename Tp::statement> &&    //
    is_composable_with<typename Tp::spec, typename Tp::statement_list> && //
    is_list_of<typename Tp::spec, typename Tp::id> &&                     //
    is_list_of<typename Tp::file, typename Tp::spec> &&                   //
    can_print<typename Tp::print, typename Tp::file> &&                   //
    true;

namespace impl {
  using namespace m4c0::parser;

  static constexpr const auto spaces = many(skip(match_any_of(" \t\r\n")));

  static constexpr const auto lparen = skip(match('('));
  static constexpr const auto rparen = skip(match(')'));
  static constexpr const auto colon = skip(match(':'));
  static constexpr const auto token_chars = at_least_one(skip(match_none_of(" \t\r\n():")));

  template<typename Tp>
  static constexpr const auto token = spaces & tokenise(token_chars) & [](input_t v) {
    return Tp { v };
  };

  template<typename LTp, typename TTp>
  static constexpr const auto list = spaces + many(token<TTp>, LTp {}) + spaces;

  template<typename LTp, typename TTp>
  static constexpr const auto params = lparen + list<LTp, TTp> + rparen + spaces;
}

template<typename Config>
requires valid_config<Config>
static auto parse(std::istream & in) noexcept {
  using file_t = typename Config::file;
  using id_t = typename Config::id;
  using param_t = typename Config::param;
  using param_list_t = typename Config::param_list;
  using print_t = typename Config::print;
  using spec_t = typename Config::spec;
  using stmt_t = typename Config::statement;
  using stmt_list_t = typename Config::statement_list;

  static constexpr const auto ids = impl::list<spec_t, id_t>;

  static constexpr const auto statement = impl::token<stmt_t> + impl::params<param_list_t, param_t>;
  static constexpr const auto statement_list = at_least_one(statement, stmt_list_t {});

  static constexpr const auto spec = ids + impl::colon + impl::spaces + statement_list + impl::spaces;

  static constexpr const auto file = many(spec, file_t {}) + m4c0::parser::eof() | "Invalid statement";

  std::string str { std::istreambuf_iterator<char> { in }, {} };
  return file({ str.data(), str.length() }) % print_t {};
}

class dummy {
public:
  explicit dummy(m4c0::parser::input_t token) noexcept {
  }
};
template<typename Of>
class dummy_list {
public:
  dummy_list operator+(const Of & /*o*/) const noexcept {
    return dummy_list {};
  }
};
class stmt {
public:
  explicit stmt(m4c0::parser::input_t token) noexcept {};
  stmt operator+(const dummy_list<dummy> & /*o*/) const noexcept {
    return *this;
  }
};

class spec {
public:
  spec operator+(const dummy & /*o*/) const noexcept {
    return *this;
  }
  spec operator+(const dummy_list<stmt> & /*o*/) const noexcept {
    return *this;
  }
};
class file {
public:
  file operator+(const spec & /*o*/) const noexcept {
    return *this;
  }
};

struct print {
  int operator()(file /*f*/, m4c0::parser::input_t /*rem*/) {
    return EXIT_SUCCESS;
  }
  int operator()(m4c0::parser::input_t n, m4c0::parser::input_t rem) {
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

struct config {
  using id = ::dummy;

  using file = ::file;

  using param = ::dummy;
  using param_list = ::dummy_list<param>;

  using statement = ::stmt;
  using statement_list = ::dummy_list<statement>;

  using spec = ::spec;

  using print = ::print;
};

int main() {
  return parse<config>(std::cin);
}
