#include <iostream>
#include <string>
using namespace std;
int main() {
  string polygon = "((((12.23 32323, 232323 235949, 59853 2020332))))";
  size_t pos1 = polygon.find('(');
  cout << "pos1: " << pos1 << '\n';
  size_t pos2 = polygon.find(')');
  string coordinates = polygon.substr(pos1, pos2);
  cout << "coordinates: " << coordinates << '\n';
  std::string s1 = "";
  for (int i = 0; i < coordinates.length(); ++i) {
    if (coordinates[i] == '(') {
      continue;
    } else {
      s1 += coordinates[i];
    }
  }
  cout << "cleaned coordinates: " << s1 << '\n';
}
