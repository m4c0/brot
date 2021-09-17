#include "parser.hpp"

class dummy {
public:
  explicit dummy(brot::parser::input_t token) noexcept {
  }
};
template<typename Of>
class dummy_list {
public:
  dummy_list operator+(const Of & /*o*/) const noexcept {
    return dummy_list {};
  }
};
class stmt {
public:
  explicit stmt(brot::parser::input_t token) noexcept {};
  stmt operator+(const dummy_list<dummy> & /*o*/) const noexcept {
    return *this;
  }
};

class spec {
public:
  spec operator+(const dummy & /*o*/) const noexcept {
    return *this;
  }
  spec operator+(const dummy_list<stmt> & /*o*/) const noexcept {
    return *this;
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
  using id = ::dummy;

  using file = ::file;

  using param = ::dummy;
  using param_list = ::dummy_list<param>;

  using statement = ::stmt;
  using statement_list = ::dummy_list<statement>;

  using spec = ::spec;

  using print = ::print;
};

int main() {
  return brot::parser::parse<config>(std::cin);
}
