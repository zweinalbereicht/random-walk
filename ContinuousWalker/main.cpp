#include <iostream>
#include <iterator>
#include <math.h>
#include <set>
#include <stdlib.h>
double mod_double(double x, double y) {
  if (x > 0) {
    return fmod(x, y);
  } else {
    return fmod(y + fmod(x, y), y);
  }
}

int main(int argc, char *argv[]) {
  int lala = 0;
  lala = -1;
  if (1 <= 2 <= 3) {
    std::cout << "in here" << std::endl;
  } else {
    std::cout << "in there" << std::endl;
  }
  std::cout << (-1.0 < -0.1 && -0.1 < 0) << std::endl;
  std::cout << (1 < 2) << std::endl;
}
