#include "brot/parser.hpp"
#include "brot/utils.hpp"
#include "m4c0/parser/numeric.hpp"
#include "m4c0/units.hpp"

namespace brot::units::impl {
  using m4c0::units::meter;
  using namespace parser::impl;

  static constexpr auto inches() {
    return match_u32() + skip(match("in")) & meter::from_inch;
  }
  static constexpr auto mils() {
    return match_u32() + skip(match("mil")) & meter::from_mil;
  }
  static constexpr auto millimeters() {
    return match_u32() + skip(match("mm")) & meter::from_mm;
  }
  static constexpr auto micrometers() {
    return match_u32() + skip(match("um")) & meter::from_um;
  }

  static constexpr auto parser() {
    return inches() | mils() | millimeters() | micrometers();
  }
}
namespace brot::units {
  class value {
    m4c0::units::meter m_value = m4c0::units::meter::nil();

  public:
    constexpr value() noexcept = default;
    constexpr explicit value(m4c0::units::meter v) : m_value(v) {
    }

    [[nodiscard]] constexpr auto operator*() const noexcept {
      return m_value;
    }
    [[nodiscard]] constexpr auto operator->() const noexcept {
      return &m_value;
    }
  };

  template<class T>
  static constexpr auto parser(m4c0::parser::input_t name) {
    return parser::parameter(name, impl::parser()) & to<T>();
  }
}
