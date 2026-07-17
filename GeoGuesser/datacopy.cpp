#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Point {
  float longitude_; // längengrad, col, x-Achse
  float latitude_;  // breitengrad, row, y-Achse
};

vector<Point> parseLine(const string &input) {
  string slicedInput;
  string objectName;
  
  objectName = input.substr(0, input.find('\t'));
  objectCoordinates = input.substr(input.find('\t') + 1);
  stringstream coordinates = coordinates;
  string openBrackets;
  string closeBracket;
  float longitude_;
  float latitude_;
  char comma;
  vector<Point> v1;
  while (coordinates >> obenBrackets >> longitude_ >> latitude_ >> comma) {
	Point p1;
	v1.push_back(p1{longitude, latitude});
  }
}

int main() {
  string line;
  ifstream pointsFile("./tf-buildings.tsv");
  vector<vector<Point>> vectorPoints;
  cout << line;
  while (getline(pointsFile, line)) {
    vectorPoints.push_back(parseLine(line));
  }
}
