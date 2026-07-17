#include <fstream>
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
  int count{0};
  for (int i = 0; i < input.length(); ++i) {
    if (input[i] == 'P' || input[i] == 'M') {
      break;
    } else {
      objectName += input[i];
      ++count;
    }
  }
  objectName = input.substr(1, count - 4);
  slicedInput = input.substr(count);
  size_t start = slicedInput.find_first_of('(');
  size_t slicedInputLength = slicedInput.find_last_of(')') - start;
  slicedInput = slicedInput.substr(start, slicedInputLength);
  int j{0};
  while (j < slicedInput.length()) {
    if (slicedInput[j] == '(') {
      slicedInput.replace(j, 1, "");
      j = 0;
    } else if (slicedInput[j] == ')') {
      slicedInput.replace(j, 1, "");
      j += 1;
    } else if (slicedInput[j] == ',') {
      slicedInput.replace(j, 1, " ");
      j += 1;
    } else {
      j += 1;
    }
  }
  slicedInput.append(" ");
  count = 0;
  string lonString;
  string latString;
  vector<Point> v;
  for (int k = 0; k < slicedInput.length(); ++k) {
    if (slicedInput[k] == ' ') {
      count += 1;
      if (count == 2) {
        count = 0;

        float lonFloat = stof(lonString);
        float latFloat = stof(latString);

        lonString = "";
        latString = "";

        Point p{lonFloat, latFloat};
        v.push_back(p);
      }
    } else if (count == 1) {
      latString += slicedInput[k];
    }
    lonString += slicedInput[k];
  }
  return v;
}

int main() {
  string line;
  ifstream pointsFile("./tf-buildings.tsv");
  vector<vector<Point>> vectorPoints;
  while (getline(pointsFile, line)) {
    vectorPoints.push_back(parseLine(line));
  }
  for (auto &vec : vectorPoints) {
	cout << vec << "\n";
  }
}
