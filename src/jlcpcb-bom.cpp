#include "brot/composer.hpp"

namespace brot::tools::jlcpcb {
  class bom {
    std::string_view m_designator;
    std::string_view m_comment {};
    std::string_view m_footprint {};
    std::string_view m_part_no {};
    bool m_valid {};

    friend std::ostream & operator<<(std::ostream & o, const bom & e);

  public:
    explicit constexpr bom(parser::tokens::name n) noexcept : m_designator(to_sv(n)) {
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

  std::ostream & operator<<(std::ostream & o, const bom & e) {
    if (!e.m_valid) return o;
    return o << e.m_designator << ", " << e.m_comment << ", " << e.m_footprint << ", " << e.m_part_no << "\n";
  }
}

int main() {
  std::cout << "Designator, Comment, Footprint, JLCPCB Part #\n";
  return brot::composer::basic<brot::tools::jlcpcb::bom>::run();
}
