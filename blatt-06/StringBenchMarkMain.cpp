#include "./String.h"
#include <cstdlib> // For random number.
#include <ctime>   // For time measuring.

int main() {
  char tmpBuffer[101];
  char basisNum = '1';
  int n = rand() % 6000;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 100; j++) {
      tmpBuffer[j] = basisNum + (rand() % 9);
    }
    tmpBuffer[100] = '\0';
    String tmp;      // Calls the constructor.
    tmp = tmpBuffer; // Calls the copy assignment operator.
    String s1 = tmp; // Calls the copy constructor.
    auto startWithCopy = clock();
    s1.sortWithCopy();
    auto endWithCopy = clock();
    double durationWithCopy =
        (endWithCopy - startWithCopy) / double(CLOCKS_PER_SEC);
    String s2 = std::move(tmp); // Calls the move constructor.
    s2.sortWithCopy;
  }
}
