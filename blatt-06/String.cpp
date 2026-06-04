// Created by eh295
#include "./String.h"
#include <cstdio>
#include <cstdlib>

String::String() {
  sizeOfString_ = 0;
  characters_ = new char[1];
  characters_[0] = '\0';
}

size_t String::size() { return sizeOfString_; }

const char* String::c_str() { return const characters_; }
