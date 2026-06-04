// Created by eh295
#include <cstdio>
#include <cstdlib>
class String {
public:
  size_t size();
  const char* c_str();
  String();

private:
  size_t sizeOfString_;
  char* characters_;  
};

class StringSorter {
  void sorter(int arg);
};
