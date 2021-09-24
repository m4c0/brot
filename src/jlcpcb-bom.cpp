#include "brot/iostream.hpp"
#include "brot/parser.hpp"
#include "brot/utils.hpp"

namespace brot::tools::jlcpcb::bom {
  using namespace brot::parser;

  class param_pair {
    std::string_view m_name;
    std::string_view m_value {};

    explicit constexpr param_pair(std::string_view n, std::string_view v) noexcept : m_name(n), m_value(v) {
    }

  public:
    explicit constexpr param_pair(tokens::name n) noexcept : m_name(to_sv(n)) {
    }
    constexpr auto operator+(tokens::value v) const noexcept {
      return param_pair { m_name, to_sv(v) };
    }

    constexpr bool operator==(std::string_view n) const noexcept {
      return n == m_name;
    }

    constexpr auto operator*() const noexcept {
      return m_value;
    }
  };

  class entry {
    std::string_view m_designator;
    std::string_view m_comment {};
    std::string_view m_footprint {};
    std::string_view m_part_no {};
    bool m_valid {};

    friend std::ostream & operator<<(std::ostream & o, const entry & e);

  public:
    explicit constexpr entry(tokens::name n) noexcept : m_designator(to_sv(n)) {
    }

    constexpr auto operator+(param_pair p) const noexcept {
      auto res = *this;
      if (p == "comment") {
        res.m_comment = *p;
      } else if (p == "footprint") {
        res.m_footprint = *p;
      } else if (p == "jlcpcb") {
        res.m_part_no = *p;
      } else if (p == "jlcpcb_bom") {
        res.m_valid = true;
      }
      return res;
    }
  };

  std::ostream & operator<<(std::ostream & o, const entry & e) {
    if (!e.m_valid) return o;
    return o << e.m_designator << ", " << e.m_comment << ", " << e.m_footprint << ", " << e.m_part_no << "\n";
  }

  static constexpr const auto cname = compo_name(name) & to<entry>();
  static constexpr const auto pname = name & to<param_pair>();
  static constexpr const auto param = parameter(pname, value);

  static constexpr const auto init = constant(m4c0::parser::nil {});
  static constexpr const auto compo = component(cname, param) & iostream::print();
  static constexpr const auto parser = file(init, skip(compo));

  static auto run() {
    std::cout << "Designator, Comment, Footprint, JLCPCB Part #\n";
    return iostream::parse_cin(parser);
  }
}

int main() {
  return brot::tools::jlcpcb::bom::run();
}
