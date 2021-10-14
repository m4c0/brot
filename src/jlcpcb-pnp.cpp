#include "brot/composer.hpp"

namespace brot::tools::jlcpcb {
  class pnp : composer::compo {
    std::string_view m_mid_x {};
    std::string_view m_mid_y {};
    std::string_view m_rotation {};
    bool m_valid {};

    friend std::ostream & operator<<(std::ostream & o, const pnp & e);

  public:
    using compo::compo;

    constexpr auto operator+(param_pair p) const noexcept {
      auto res = *this;
      if (p == "pcb_x") {
        res.m_mid_x = *p;
      } else if (p == "pcb_y") {
        res.m_mid_y = *p;
      } else if (p == "pcb_rotation") {
        res.m_rotation = *p;
      } else if (p == "jlcpcb_bom") {
        res.m_valid = true;
      }
      return res;
    }
  };
  std::ostream & operator<<(std::ostream & o, const pnp & e) {
    if (!e.m_valid) return o;
    return o << e.designator() << ", " << e.m_mid_x << ", " << e.m_mid_y << ", " << e.m_rotation << "\n";
  }
}

int main() {
  std::cout << "Designator, Mid X, Mid Y, Layer, Rotation\n";
  return brot::composer::basic<brot::tools::jlcpcb::pnp>::run();
}
