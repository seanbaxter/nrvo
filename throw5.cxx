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
    printf("b_t %p\n", this);
  }
  ~b_t() noexcept(false) {
    printf("~b_t %p\n", this);
    throw 5;
  }
};

a_t func(bool cond) {
  // ~b_t should destroy the named temporary.
  a_t a;
  if(cond) {
    b_t b;      
    return a;   // should do NRVO. But then b should throw. 
  }
  return a;
}

int main() {
  try {
    a_t a = func(true);
    printf("func returned\n");

  } catch(...) {
    printf("Exception caught\n");
  }
}