#pragma once

#include "brot/parser.hpp"
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

  class param_pair {
    std::string_view m_name;
    std::string_view m_value {};

    explicit constexpr param_pair(std::string_view n, std::string_view v) noexcept : m_name(n), m_value(v) {
    }

  public:
    explicit constexpr param_pair(parser::tokens::name n) noexcept : m_name(to_sv(n)) {
    }
    constexpr auto operator+(parser::tokens::value v) const noexcept {
      return param_pair { m_name, to_sv(v) };
    }

    constexpr bool operator==(std::string_view n) const noexcept {
      return n == m_name;
    }

    constexpr auto operator*() const noexcept {
      return m_value;
    }
  };
}
