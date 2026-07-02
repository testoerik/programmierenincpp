#include "./TerminalManager.h"

class MockTerminalManager : public TerminalManager {
public:
  // Constructor.
  explicit MockTerminalManager(int a, int b);

  // Checks whether the pixel is drawn or not.
  bool isPixelDrawn(int row, int col);
  void drawPixel(int row, int col, bool inverse, float intensity) override {
  void refresh() override;

  protected:
    std::unordered_map<bool drawedPixel, int pos> expectedPixels;
  };
