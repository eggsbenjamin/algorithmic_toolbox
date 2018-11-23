#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <math.h>
#include <cmath>
#include <assert.h>
#include <float.h>

using std::vector;
using std::string;
using std::pair;
using std::min;

struct point {
  int x, y;
};

void printVec(std::vector<point> vec) {
  printf("[");
  for(size_t i = 0; i < vec.size(); i++) {
    printf(" (%d, %d) ", vec[i].x, vec[i].y);
  }
  printf("]\n");
}

double dist(point p1, point p2) {
  return sqrt(pow(p2.x-p1.x, 2)+pow(p2.y-p1.y, 2));
}

double brute_force_minimal_distance(vector<point> points, double m) {
  for(size_t i = 0; i < points.size(); i++) {
    for(size_t j = i; j < points.size(); j++) {
      if(i != j) {
        m = min(dist(points[i], points[j]), m);
      }
    }
  }

  return m;
}

double minimal_distance(vector<point> points) {
  if(points.size() <= 3) return brute_force_minimal_distance(points, FLT_MAX);

  int mid = points.size()/2;
  int d1 = minimal_distance(vector<point>(points.begin(), points.begin()+mid));
  int d2 = minimal_distance(vector<point>(points.begin()+mid, points.end()));
  double m = min(d1, d2);

  vector<point> closerY;
  for(size_t i = 0; i < points.size(); i++) {
    if(abs(points[i].x - points[mid].x) < m) closerY.push_back(points[i]);
  }

  std::sort(closerY.begin(), closerY.end(), [](point a, point b) { return a.y < b.y; });
  return min(m, brute_force_minimal_distance(closerY, m));
}

void test_solution() {
  struct test {
    string title;
    vector<point> points;
    double expected;
  };

  vector<test> tests = vector<test>{
    {
      "sample 1",
      {{0,0}, {3,4}},
      5,
    },
    {
      "sample 2",
      {{7,7}, {1,100}, {4,8}, {7,7}},
      0,
    },
    {
      "sample 3",
      {{4,4}, {-2,-2}, {-3,-4}, {-1,3}, {2,3}, {-4,0}, {1,1}, {-1,-1}, {3,-1}, {-4,2}, {-2,4}},
      1.414213,
    },
  };

  for(size_t i = 0; i < tests.size(); i++) {
    std::sort(tests[i].points.begin(), tests[i].points.end(), [](point a, point b) { return a.x < b.x; });
    double result = minimal_distance(tests[i].points);
    printVec(tests[i].points);
    std::cout << "result=" << result << " expected=" << tests[i].expected << '\n';
    assert(result == tests[i].expected);
  }
}

int main() {
  size_t n;
  std::cin >> n;
  vector<point> points(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> points[i].x >> points[i].y;
  }
  std::sort(points.begin(), points.end(), [](point a, point b) { return a.x < b.x; });
  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(points) << "\n";
}
