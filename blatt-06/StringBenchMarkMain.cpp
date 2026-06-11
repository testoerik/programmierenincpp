#include "./String.h"
#include <cstdlib> // For random number.
#include <ctime>   // For time measuring.

int main() {
  char basisNum = '1';
  srand(time(nullptr));

  // Generate random number between 10001 and 1999.
  int n = rand() % 10000 + 10000;

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
  printf("Sorting %d strings with copy...\n", n);
  auto startCopy = clock();
  sorterCopy.sortWithCopy();
  auto endCopy = clock();
  double timeCopy = (endCopy - startCopy) / (double)CLOCKS_PER_SEC;
  printf("Time for sorting %d strings with copy: %.2f seconds.\n", n, timeCopy);
  printf("Sorting %d strings with move...\n", n);
  auto startMove = clock();
  sorterMove.sortWithMove();
  auto endMove = clock();
  double timeMove = (endMove - startMove) / (double)CLOCKS_PER_SEC;
  printf("Time for sorting %d strings with move: %.2f seconds.\n", n, timeMove);
  printf(
      "Sorting %d strings with move is %.2f seconds faster than with copy!\n",
      n, timeCopy - timeMove);
}
