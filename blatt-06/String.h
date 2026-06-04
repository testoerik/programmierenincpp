// Created by eh295
#include <cstdio>
#include <cstdlib>
class String {
public:
  size_t size() const;
  const char *c_str() const;
  String &operator=(const char *s);
  String(const char *s);
  String();
  ~String();

private:
  size_t sizeOfString_;
  char *characters_;
};

class StringSorter {
  void sorter(int arg);
};
