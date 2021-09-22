#pragma once

#include "parser.hpp"

#include <iostream>

namespace brot::printer {
  static auto begin_spec(auto name) {
    std::cout << name << ":\n";
    return parser::nil {};
  }
  static auto add_parameter(auto name, auto value) {
    std::cout << "  " << name << "(" << value << ")\n";
    return parser::nil {};
  }
}
