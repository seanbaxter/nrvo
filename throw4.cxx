#include <cstdio>

struct b_t {
  b_t(bool throws) : throws(throws) { 
    printf("b_t\n");
  }
  ~b_t() noexcept(false) {
    printf("~b_t\n");
    if(throws)
      throw 5;
  }
  bool throws;
};

b_t func() {
  // ~b_t should destroy the named temporary.
  b_t a(true);
  return b_t(false);
}

int main() {
  try {
    b_t ret = func();
    printf("func returned\n");

  } catch(...) {
    printf("Exception caught\n");
  }
}