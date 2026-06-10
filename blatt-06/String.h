#include <cstdio>
class String {
public:
  // Constructor.
  String();

  // Copy constructor.
  String(const String &s);

  // Move constructor.
  String(String &&other);

  size_t size() const;

  const char *c_str() const;

  // Overload of the assignement operator.
  String &operator=(const char *s);

  // Overload of the copy assignement operator.
  String &operator=(const String &s);

  // Move assignment operator.
  String &operator=(String &&other);

  // Destructor, whichs deletes the characters_ member
  ~String();

private:
  size_t sizeOfString_;
  char *characters_;
};

class StringSorter {
public:
  // Constructor, which takes an int as an argument.
  StringSorter(const size_t &num);
  size_t size();
  String &operator[](int index);
  void swapWithCopy(size_t x, size_t y);
  void swapWithMove(size_t x, size_t y);
  void sortWithCopy();
  void sortWithMove();
  // Destructor, which deletes the member strings_;
  ~StringSorter();

private:
  String *strings_;
  size_t stringsNum_;
};
