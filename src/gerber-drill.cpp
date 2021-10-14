#include "brot/composer.hpp"
#include "brot/units.hpp"
#include "m4c0/parser/constants.hpp"
#include "m4c0/parser/numeric.hpp"

#include <algorithm>
#include <iomanip>
#include <variant>
#include <vector>

namespace brot::tools::gerber {
  using namespace brot::parser;
  using namespace m4c0::parser;

  struct drill_size : units::value {
    using value::value;
  };
  struct drill_x : units::value {
    using value::value;
  };
  struct drill_y : units::value {
    using value::value;
  };
  using drill_param = std::variant<std::monostate, drill_size, drill_x, drill_y>;

  class drill : drill_size, drill_x, drill_y {
  public:
    [[nodiscard]] constexpr auto size() const noexcept {
      return static_cast<const drill_size &>(*this)->to_mm<double>();
    }
    [[nodiscard]] constexpr auto x() const noexcept {
      return static_cast<const drill_x &>(*this)->to_mm<double>();
    }
    [[nodiscard]] constexpr auto y() const noexcept {
      return static_cast<const drill_y &>(*this)->to_mm<double>();
    }

    template<typename T>
    [[nodiscard]] constexpr drill operator()(const T & p) const noexcept {
      drill res = *this;
      static_cast<T &>(res) = p;
      return res;
    }
    [[nodiscard]] constexpr drill operator()(const std::monostate & /*p*/) const noexcept {
      return *this;
    }

    [[nodiscard]] constexpr drill operator+(const drill_param & p) const noexcept {
      return std::visit(*this, p);
    }
  };

  class drill_set {
    std::vector<drill> * m_set;

  public:
    constexpr explicit drill_set(std::vector<drill> * s) noexcept : m_set(s) {
    }
    [[nodiscard]] constexpr drill_set operator+(const drill & p) const noexcept {
      if (p.size() > 0.0) m_set->push_back(p);
      return *this;
    }

    [[nodiscard]] auto begin() const noexcept {
      return m_set->begin();
    }
    [[nodiscard]] auto end() const noexcept {
      return m_set->end();
    }
  };
  static std::ostream & operator<<(std::ostream & o, const drill_set & s) {
    std::sort(s.begin(), s.end(), [](const drill & a, const drill & b) noexcept {
      return a.size() < b.size() || a.y() < b.y() || a.x() < b.x();
    });

    double ls = 0;
    int id = 0;

    o << "M48\nMETRIC\n";
    o << std::fixed << std::setfill('0');
    for (const auto & d : s) {
      if (d.size() <= ls) continue;
      ls = d.size();
      id++;
      o << "T" << std::setw(3) << id;
      o << "C" << std::setw(0) << ls << "\n";
    }
    o << "%\nG05\nG90\n"; // Drill absolute

    ls = 0;
    id = 0;
    for (const auto & d : s) {
      if (d.size() > ls) {
        ls = d.size();
        id++;
        o << "T" << std::setw(3) << id << "\n";
      }
      o << "X" << d.x() << "Y" << d.y() << "\n";
    }
    o << std::defaultfloat;
    o << "M30\n";
    return o;
  }

  static constexpr const auto pcb_drill = units::parser<drill_size>("pcb_drill") & to<drill_param>();
  static constexpr const auto pcb_x = units::parser<drill_x>("pcb_x") & to<drill_param>();
  static constexpr const auto pcb_y = units::parser<drill_y>("pcb_y") & to<drill_param>();
  static constexpr const auto other_param = parameter() & constant(drill_param {});
  static constexpr const auto param = pcb_drill | pcb_x | pcb_y | other_param;

  static constexpr const auto cname = parser::compo_name(parser::name) & [](auto /*v*/) noexcept {
    return drill {};
  };
  static constexpr const auto compo = parser::component(cname, param);

  static auto run() {
    std::vector<drill> s {};
    const auto parser = parser::file(constant(drill_set { &s }), compo) & iostream::print();
    return iostream::parse_cin(parser);
  }
}

int main() {
  return brot::tools::gerber::run();
}
