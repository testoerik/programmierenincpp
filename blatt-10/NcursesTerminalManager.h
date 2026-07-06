// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.
//

#pragma once
#include "./TerminalManager.h"
#include <cstddef>

class NcursesTerminalManager : public TerminalManager {
public:
  NcursesTerminalManager();
  UserInput getUserInput();
  void drawPixel(int row, int col, bool inverse, float intensity) override;
  void drawString(int row, int col, const char *output, float intensity = 1.0);
  void refresh() override;
  int numColors();
  ~NcursesTerminalManager();

private:
  size_t convertIntensityToColor(float intensity) const;
};
