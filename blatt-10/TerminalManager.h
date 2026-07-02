class TerminalManager {
public:
  virtual void drawPixel(int row, int col, bool inverse, float intensity);
  virtual void refresh();
  virtual ~TerminalManager();
};
