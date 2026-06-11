#include "./String.h"
#include <cstdlib> // For random number.
#include <ctime>   // For time measuring.

int main() {
  char basisNum = '1';
  int n = rand() % 6000;

  StringSorter sorterCopy(n);
  StringSorter sorterMove(n);
  for (int i = 0; i < n; i++) {
    char tmpBuffer[101];
    for (int j = 0; j < 100; j++) {
      tmpBuffer[j] = basisNum + (rand() % 9);
    }
    tmpBuffer[100] = '\0';
    sorterCopy[i] = tmpBuffer;
    sorterMove[i] = tmpBuffer;
  }
  auto startCopy = clock();
  sorterCopy.sortWithCopy();
  auto endCopy = clock();
  double timeCopy = (endCopy - startCopy) / (double)CLOCKS_PER_SEC;
  printf("Time for sorting %d objects with copy: %.2f seconds\n", n, timeCopy);
  auto startMove = clock();
  sorterMove.sortWithMove();
  auto endMove = clock();
  double timeMove = (endMove - startMove) / (double)CLOCKS_PER_SEC;
  printf("Time for sorting %d objects with move: %.2f seconds\n", n, timeMove);
}
