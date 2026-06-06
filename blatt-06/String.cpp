// Created by eh295
#include "./String.h"
#include <cstdio>
#include <cstdlib>

String::String() {
  sizeOfString_ = 0;
  characters_ = new char[1];
  characters_[0] = '\0';
}
size_t String::size() const { return sizeOfString_; }

const char *String::c_str() const { return characters_; }

String &String::operator=(const char *s) {
  delete[] characters_;
  int i = 0;
  int sizeOfString = 0;
  while (true) {
    if (s[i] == '\0') {
      break;
    } else {
      i++;
      sizeOfString++;
    }
  }
  characters_ = new char[sizeOfString + 1];
  for (int i = 0; i < sizeOfString; i++) {
    characters_[i] = s[i];
  }
  characters_[sizeOfString] = '\0';
  sizeOfString_ = sizeOfString;
  return *this;
}
String::String(const String &s) {
  sizeOfString_ = s.sizeOfString_;
  characters_ = new char[sizeOfString_ + 1];
  for (size_t i = 0; i < s.sizeOfString_; i++) {
    characters_[i] = s.characters_[i];
  }
  characters_[sizeOfString_] = '\0';
}
String &String::operator=(const String &s) {
  if (this == &s) {
    return *this;
  }
  delete[] characters_;
  sizeOfString_ = s.sizeOfString_;
  characters_ = new char[sizeOfString_ + 1];
  for (size_t i = 0; i < s.sizeOfString_; i++) {
    characters_[i] = s.characters_[i];
  }
  characters_[sizeOfString_] = '\0';
  return *this;
}
StringSorter::StringSorter(const size_t &num) {
  num_ = num;
  strings_ = new String[num_ + 1];
  tmp_ = strings_;
}
size_t StringSorter::size() { return num_; }
String &StringSorter::operator[](int index) { return strings_[index]; }
char *StringSorter::swap(int x, int y) {
  strings_[x] = tmp_[y];
  strings_[y] = tmpa_[x];  
  return strings_;
}
String::~String() { delete[] characters_; }
StringSorter::~StringSorter() { delete[] strings_; }
