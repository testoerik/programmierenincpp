#include "./String.h"

String::String() {
  string_ = new String[1];
  sizeOfString = 0;
}
const char *String::c_str() const {return string_} size_t String::size() {
  return sizeOfString_;
}
String::~String() { delete[] string_; }
