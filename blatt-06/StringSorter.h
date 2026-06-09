#include <cstdio>
#include "./String.h"
class StringSorter {
public:
  // Constructor.
  StringSorter(const int &n);
  // Returns the size of the given string.
  // Index operator.
  char *operator[](int index);
  // Destructor.
  ~StringSorter();

private:
};
