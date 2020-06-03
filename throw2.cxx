#include <cstdio>

struct a_t { 
  a_t() { 
    printf("a_t %p\n", this);
  }
  ~a_t() {
    printf("~a_t %p\n", this);
  }
};

struct b_t {
  b_t() { 
    printf("b_t\n");
  }
  ~b_t() noexcept(false) {
    printf("~b_t\n");
    throw 5;
  }
};

a_t func() {
  // ~b_t should destroy the named temporary.
  a_t a;
  b_t b;
  return a;
}

int main() {
  try {
    a_t a = func();
    printf("func returned\n");

  } catch(...) {
    printf("Exception caught\n");
  }
}