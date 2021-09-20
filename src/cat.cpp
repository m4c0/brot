#include "parser.hpp"

template<typename Of>
class dummy_list {
public:
  dummy_list operator+(const Of & /*o*/) const noexcept {
    return dummy_list {};
  }
};
class stmt {
public:
  stmt(brot::parser::input_t name, brot::parser::input_t params) noexcept {};
};

class spec {
public:
  spec(brot::parser::input_t token, const dummy_list<stmt> & stmts) noexcept {
  }
};
class file {
public:
  file operator+(const spec & /*o*/) const noexcept {
    return *this;
  }
};

struct print {
  bool operator()(file /*f*/) {
    return EXIT_SUCCESS;
  }
};

struct config {
  using file = ::file;

  using statement = ::stmt;
  using statement_list = ::dummy_list<statement>;

  using spec = ::spec;

  using print = ::print;
};

int main() {
  return brot::parser::parse<config>(std::cin);
}
