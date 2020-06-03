#include <cstdio>

struct X {
  char s;
  bool throws;

  ~X() noexcept(false) {
    printf("~%c\n", s);
    if (throws) throw 0;
  }

  X(X&& o) = delete;

  explicit X(char s, bool throws = false) 
    : s(s), throws(throws)
  {
    printf("%c\n", s);
  }
};

// correct order of destruction: ma
X test1() {
  X m('m', true);
  return X('a');
}

// correct order of destruction: dbmca
X test2() {
  X a('a');
  X m('m', true);
  X b('b');
  X c('c');
  X d('d');
  return c;
}

// correct order of destruction: mab
X test3() {
  X a('a');
  X b('b');
  try {
    X m('m', true);
    return b;
  } catch (...) { }
  return b;  // b is returned here
}

// correct order of destruction if cond:  mbad
// correct order of destruction if !cond: bmcad
X test4(bool cond) {
  X a('a');
  try {
    X m('m', true);
    {
      X b('b');
      if (cond) {
        return b;
      }
    }
    {
      X c('c');
      return c;
    }
  } catch (...) { }
  return X('d');
}

int main() {
  try { test1(); } catch(...) {} puts("");
  try { test2(); } catch(...) {} puts("");
  test3(); puts("");
  test4(true); puts("");
  test4(false); puts("");
}