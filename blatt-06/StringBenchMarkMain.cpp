#include "./String.cpp"
#include <cstdlib> // For random number.
#include <ctime>   // For time measuring.

int main() {
  char tmpBuffer[101];
  int n = rand() % 100;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 100; j++) {
      tempBuffer[i] = rand() % 10;
    }
  }
  tmpBuffer[100] = '\0';
  String tmp;
  tmp = tmpBuffer;
}
