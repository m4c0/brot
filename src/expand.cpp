#include "brot/iostream.hpp"
#include "brot/parser.hpp"
#include "brot/utils.hpp"

#include <string_view>
#include <unordered_map>

namespace brot::tools::expand {
  using namespace brot::parser;

  using compo_map = std::unordered_map<std::string_view, std::string_view>;
  using include_map = std::unordered_map<std::string_view, compo_map>;

  struct param_fn {
    tokens::name name;
    bool is_include;
  };
  static constexpr auto to_param_fn(bool is_inc) noexcept {
    return [is_inc](tokens::name n) noexcept {
      return param_fn { n, is_inc };
    };
  }

  struct param_pair : public param_fn {
    tokens::value value;
  };
  static constexpr auto operator+(param_fn fn, tokens::value v) noexcept {
    return param_pair { fn, v };
  }

  struct compo_builder {
    std::string_view name;
    include_map * map;
  };
  static compo_builder operator+(compo_builder c, param_pair var) {
    auto & params = (*c.map)[c.name];
    if (var.is_include) {
      for (auto & kv : c.map->at(to_sv(var.value))) {
        params.insert_or_assign(kv.first, kv.second);
      }
    } else {
      params.insert_or_assign(to_sv(var.name), to_sv(var.value));
    }
    return c;
  }

  struct file_builder {};
  static file_builder operator+(file_builder /*f*/, compo_builder c) {
    iostream::print_name(c.name);
    for (auto & kv : c.map->at(c.name)) {
      iostream::print_param(kv.first, kv.second);
    }
    return {};
  }

  static constexpr const auto cname = compo_name(name);

  static constexpr const auto include_token = tokenise<token_ids::name>(m4c0::parser::match("include"));
  static constexpr const auto include_name = include_token & to_param_fn(true);
  static constexpr const auto other_name = name & to_param_fn(false);
  static constexpr const auto param_name = include_name | other_name;

  static constexpr const auto param = parameter(param_name, value);

  static constexpr const auto init = m4c0::parser::constant(file_builder {});

  static auto run() {
    std::unordered_map<std::string_view, compo_map> specs {};

    const auto cnb = cname & [&specs](tokens::name name) {
      const auto sv = to_sv(name);
      return compo_builder { sv, &specs };
    };

    const auto valid_param = param && [&specs](param_pair pair) -> bool {
      return !pair.is_include || specs.contains(to_sv(pair.value));
    };
    const auto compo = component(cnb, valid_param);

    return iostream::parse_cin(file(init, compo));
  }
}

int main() {
  return brot::tools::expand::run();
}
