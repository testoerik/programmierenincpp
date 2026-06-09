#include <cstdio>
class String {
public:
  // Constructor.
  String();
  // Getter for the size of the string.
  size_t size();
  // Returns a c_str.
  const char *c_str() const;
  // Destructor.
  ~String();

private:
  // A string.
  String *string_;
  // Size of string after initialization stored in sizeOfString_.
  size_t sizeOfString_;
};
