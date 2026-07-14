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

void parseLine(const string &input) {
  size_t pos1 = input.find_first_of('(');
  size_t pos2 = input.find_last_of(')');
  string stringCoordinates = input.substr(pos1, pos2);

  int numComma = 0;
  for (int i = 0; i < stringCoordinates.length(); ++i) {
    if (stringCoordinates[i] == ',') {
      numComma++;
    }
  }
  string strLon;
  string strLat;
  for (int j = 0; j < numComma; ++j) {
    size_t posFrstBracket = stringCoordinates.find_first_of('(');
    size_t posFrstSpace = stringCoordinates.find_first_of(' ');
    size_t posFrstComma = stringCoordinates.find_first_of(',');

    float lon = stof(stringCoordinates.substr(posFrstBracket, posFrstSpace));

    cout << "lon: " << lon << '\n';
    stringCoordinates = stringCoordinates.substr(posFrstComma);
  }
}
int main() {
  string line;
  ifstream pointsFile("./tf-buildings.tsv");
  while (getline(pointsFile, line)) {
    parseLine(line);
  }
}
