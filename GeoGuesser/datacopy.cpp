#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Point {
  float longitude_; // längengrad, col, x-Achse
  float latitude_;  // breitengrad, row, y-Achse
};

void parseLine(const string &input) {
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
        }
	else if (slicedInput[j] == ')') {
		slicedInput.replace(j, 1, "");
		j += 1;
 	}
        else if (slicedInput[j] == ',') {
		slicedInput.replace(j, 1, " ");
		j += 1;
	} else {
		j += 1;
	}
   }
   cout << slicedInput;
}
int main() {
  string line;
  ifstream pointsFile("./tf-buildings.tsv");
  while (getline(pointsFile, line)) {
    parseLine(line);
  }
}
