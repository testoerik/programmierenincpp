#include "./TerminalManager.h"

class MockTerminalManager : public TerminalManager {
public:
  // Constructor.
  explicit MockTerminalManager(int numRows_, int numCols_);
};
