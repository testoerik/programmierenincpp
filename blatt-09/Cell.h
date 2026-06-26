#pragma once
#include <functional>
#include <cstddef>

struct Cell {
  int pixelRow_;
  int pixelCol_;
  // Check if we have a duplicate of Cell object.
  bool operator==(const Cell &other) const {
    return pixelRow_ == other.pixelRow_ && pixelCol_ == other.pixelCol_;
  }
};

struct CellHash {
  // Hashfunction as functor.
  std::size_t operator()(const Cell &c) const {
    std::size_t h1 = std::hash<int>{}(c.pixelRow_);
    std::size_t h2 = std::hash<int>{}(c.pixelCol_);
    // Avoid collision.
    return h1 ^ (h2 << 1);
  }
};
