#include "./String.cpp"
#include <cstdlib> // For random number.
#include <ctime>   // For time measuring.

int main() {
  StringSorter s1(100);
  StringSorter s2(std::move(s1));

  // Create a random number n.
  int n = drand48() * 256;
  for (int i = 0; i < 100; i++) {
    String tmp = std::move(drand48() * 256);
    s1[i] = tmp;
    s2[i] = tmp;
  }  
}
