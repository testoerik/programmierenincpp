#include "./StringSorter.h"
#include "./String.h"

StringSorter::StringSorter(const int &n) {
  sizeOfStringStorage_ = n;
  stringStorage_ = new char[n];
  for (int i = 0; i < n; i++) {
    stringStorage_[i].c_str() = "";
  }
  stringStorage_[n] = '\0';
}
const char *StringSorter::c_str() const { return stringsStorage_; }
size_t StringSorter::size() const { return sizeOfStringStorage_; }
StringSorter::~StringSorter() { delete[] stringStorage_; }
