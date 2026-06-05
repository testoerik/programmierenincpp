// Created by eh295
#include <cstdio>
#include <cstdlib>
class String {
public:
  size_t size() const;
  const char *c_str() const;
  // Assignement operator.
  String &operator=(const char *s);
  // Copy constructor.
  String(const String &s);
  // (Default) constructor.
  String();
  // Copy assignement operator.
  String &operator=(const String &s);
  // Default destructor.
  ~String();

private:
  size_t sizeOfString_;
  char *characters_;
};

class StringSorter {
public:
  size_t size() const;
  const char *c_str() const;
  // Constructor.
  StringSorter(const size_t &num);

private:
  size_t num_;
  char *emptStr_;
};
