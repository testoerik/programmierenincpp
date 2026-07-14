#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Point {
  float longitude_; // längengrad, col, x-Achse
  float latitude_;  // breitengrad, row, y-Achse
};

vector<Point> points;

Point parseLine(const string &input) {
  size_t pos1 = input.find('(');
  size_t pos2 = input.find(' ' + pos1);

  float lon = atof(input.data() + pos1 + 1);
  float lat = atof(input.data() + pos2 + 1);
  return Point{lon, lat};
}

int main() {
  string line;
  ifstream pointsFile("./departements.tsv");
  while (getline(pointsFile, line)) {
        points.push_back(parseLine(line));
  }
  cout << "points: " << points << '\n';
}
