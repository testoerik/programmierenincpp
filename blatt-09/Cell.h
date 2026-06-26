

struct CellHash {
  // Hashfunction as functor.
  std::size_t operator()(const Cell &c) const {
    std::size_t h1 = std::hash<int>{}(c.pixelRow_);
    std::size_t h2 = std::hash<int>{}(c.pixelCol_);
    // Avoid collision.
    return h1 ^ (h2 << 1);
  }
};
class Cell {
private:
  int pixelRow_;
  int pixelCol_;

public:
  // Check if we have a duplicate of Cell object.
  bool operator==(const Cell &other) const {
    return pixelRow_ == other.pixelRow_ && pixelCol_ == other.pixelCol_;
  }
  // Getter function which returns a reference to a unordered_map.
  std::unordered_map<Cell, int, CellHash> heatMap() { return m; }
  std::unordered_map<Cell, int, CellHash> m;
};
