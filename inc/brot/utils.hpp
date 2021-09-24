#pragma once

#include "m4c0/parser/tokeniser.hpp"

#include <string_view>
#include <type_traits>

namespace brot {
  template<typename T>
  static constexpr auto to_sv(m4c0::parser::token<T> t) noexcept {
    return std::string_view { t.value.begin(), t.value.length() };
  }

  template<typename T>
  static constexpr auto to() {
    return [](auto val) noexcept -> T {
      return T { val };
    };
  }
}
