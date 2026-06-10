#include "./String.h"
#include <cstring>
#include <utility>
//____________________________________________________________________________
String::String() {
  sizeOfString_ = 0;
  characters_ = new char[1];
  characters_[0] = '\0';
}

//____________________________________________________________________________
size_t String::size() const { return sizeOfString_; }

//____________________________________________________________________________
const char *String::c_str() const { return characters_; }

// Assignement operator.
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
  for (int j = 0; j < sizeOfString; j++) {
    characters_[j] = s[j];
  }
  characters_[sizeOfString] = '\0';
  sizeOfString_ = sizeOfString;
  return *this;
}
// Copy assignment operator.
String &String::operator=(const String &s) {
  if (this != &s) {
    delete[] characters_;
    sizeOfString_ = s.sizeOfString_;
    characters_ = new char[sizeOfString_ + 1];
    for (size_t i = 0; i < sizeOfString_; i++) {
      characters_[i] = s.characters_[i];
    }
    characters_[sizeOfString_] = '\0';
  }
  return *this;
}
// Move assignment operator.
String &String::operator=(String &&other) {
  if (this != &other) {
    // Free the memory of this object.
    delete[] characters_;
    // Rob the other object of everything it has.
    sizeOfString_ = other.sizeOfString_;
    characters_ = other.characters_;

    // Reset the other object.
    other.sizeOfString_ = 0;
    other.characters_ = nullptr;
  }
  return *this;
}

// Copy constructor.
String::String(const String &s) {
  sizeOfString_ = s.sizeOfString_;
  characters_ = new char[sizeOfString_ + 1];
  for (size_t i = 0; i < sizeOfString_; i++) {
    characters_[i] = s.characters_[i];
  }
  characters_[sizeOfString_] = '\0';
}
// Move constructor.
String::String(String &&other) {
  // Rob the other object of everything it has.
  sizeOfString_ = other.sizeOfString_;
  characters_ = other.characters_;

  // Reset the other object.
  other.sizeOfString_ = 0;
  other.characters_ = nullptr;
}
//____________________________________________________________________________
StringSorter::StringSorter(const size_t &num) {
  stringsNum_ = num;
  strings_ = new String[stringsNum_];
}

//____________________________________________________________________________
size_t StringSorter::size() { return stringsNum_; }

//____________________________________________________________________________
String &StringSorter::operator[](int index) { return strings_[index]; }

//____________________________________________________________________________
void StringSorter::swapWithCopy(size_t x, size_t y) {
  String tmp = strings_[y];
  strings_[y] = strings_[x];
  strings_[x] = tmp;
}

//_____________________________________________________________________________
void StringSorter::sortWithCopy() {
  for (size_t j = 0; j < stringsNum_; j++) {
    for (size_t i = 0; i < stringsNum_ - 1; i++) {
      if (strcmp(strings_[i].c_str(), strings_[i + 1].c_str()) > 0) {
        swapWithCopy(i, i + 1);
      } else {
        continue;
      }
    }
  }
}
void StringSorter::swapWithMove(size_t x, size_t y) {
  String tmp = std::move(strings_[x]);
  strings_[x] = std::move(strings_[y]);
  strings_[y] = std::move(tmp);
}
void StringSorter::sortWithMove() {
  for (size_t j = 0; j < stringsNum_; j++) {
    for (size_t i = 0; i < stringsNum_; i++) {
      if (strcmp(strings_[i].c_str(), strings_[i + 1].c_str()) > 0) {
        swapWithMove(i, i + 1);
      } else {
        continue;
      }
    }
  }
}
//_____________________________________________________________________________
String::~String() { delete[] characters_; }

//____________________________________________________________________________
StringSorter::~StringSorter() { delete[] strings_; }
