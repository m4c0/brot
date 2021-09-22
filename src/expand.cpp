#include "parser.hpp"
#include "printer.hpp"

#include <unordered_map>

class expand {
  using props = std::unordered_map<std::string, std::string>;

  std::unordered_map<std::string, props> m_specs {};
  props * m_current {};
  bool m_valid { true };

  static auto to_string(auto in) {
    return std::string { in.value.begin(), in.value.end() };
  }

public:
  [[nodiscard]] constexpr auto begin_spec() {
    return [this](brot::parser::tokens::spec name) {
      m_current = &m_specs[to_string(name)];
      return brot::printer::begin_spec(name);
    };
  }
  [[nodiscard]] constexpr auto add_parameter() {
    return [this](auto name, auto value) {
      const auto n = to_string(name);
      const auto v = to_string(value);

      if (n != "include") {
        m_current->emplace(n, v);
        return brot::printer::add_parameter(name, value);
      }
      if (!m_specs.contains(v)) {
        std::cout << "ERR ERR ERR ERR ERR ERR\n";
      }
      for (auto & kv : m_specs[v]) {
        m_current->emplace(kv.first, kv.second);
        brot::printer::add_parameter(kv.first, kv.second);
      }
      return brot::parser::nil {};
    };
  }
  [[nodiscard]] bool finish() const {
    return m_valid;
  }
};

int main() {
  return brot::parser::parse<expand>(std::cin);
}
