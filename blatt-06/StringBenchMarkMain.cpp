#include "./String.h"
#include <cstdlib> // For random number.
#include <ctime>   // For time measuring.

int main() {
  char basisNum = '1';
  int n = rand() % 6000;

  String sorterCopy(n);
  String sorterMove(n);
  for (int i = 0; i < n; i++) {
    char tmpBuffer[101];
    for (int j = 0; j < 100; j++) {
      tmpBuffer[j] = basisNum + (rand() % 9);
    }
    sorterCopy[i] = tmpBuffer;
    sorterMove[i] = tmpBuffer;
  }
  sorterCopy.sortWithCopy();
  sorterMove.sortWithMove();
}
