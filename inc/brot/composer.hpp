#pragma once

#include "brot/iostream.hpp"
#include "brot/parser.hpp"
#include "brot/utils.hpp"

#include <type_traits>

namespace brot::composer {
  template<typename T>
  concept basic_type = requires(T t) {
    T(std::declval<parser::tokens::name>());
    { t + std::declval<param_pair>() };
    { std::declval<std::ostream>() << t };
  };

  template<typename T>
  requires basic_type<T>
  class basic {
    static constexpr const auto cname = parser::compo_name(parser::name) & to<T>();
    static constexpr const auto pname = parser::name & to<param_pair>();
    static constexpr const auto param = parser::parameter(pname, parser::value);

    static constexpr const auto init = constant(m4c0::parser::nil {});
    static constexpr const auto compo = parser::component(cname, param) & iostream::print();
    static constexpr const auto parser = parser::file(init, skip(compo));

  public:
    static auto run() {
      return iostream::parse_cin(parser);
    }
  };
}
