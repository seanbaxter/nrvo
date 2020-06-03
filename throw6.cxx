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

b_t func(bool cond) {
  // ~b_t should destroy the named temporary.
  return cond ? b_t(true) : b_t(false);
}

int main() {
  try {
    b_t result = func(true);
    prinf("func returned\n");

  } catch(...) {
    printf("Caught exception\n");
  }

}