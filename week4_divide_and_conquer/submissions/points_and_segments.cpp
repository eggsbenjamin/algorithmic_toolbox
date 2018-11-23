#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <assert.h>

using std::vector;
using std::tuple;
using std::string;
using std::map;

#define START 0
#define POINT 1
#define END 2

void printIntVec(std::vector<int> vec) {
  printf("[");
  for(size_t i = 0; i < vec.size(); i++) {
    printf(" %d ", vec[i]);
  }
  printf("]\n");
}

void printTupleVec(vector<tuple<int, int>> vec) {
  printf("[");
  for(size_t i = 0; i < vec.size(); i++) {
    int v = std::get<0>(vec[i]);
    int type = std::get<1>(vec[i]);
    string typeStr;

    switch(type) {
      case START:
        typeStr = "S";
        break;
      case END:
        typeStr = "E";
        break;
      case POINT:
        typeStr = "P";
        break;
    }

    std::cout << " " << v << "(" << typeStr << ") ";
  }
  printf("]\n");
}

bool sortWeightedPoint(tuple<int, int> a, tuple<int, int> b) {
  int aVal = std::get<0>(a);
  int aType = std::get<1>(a);
  int bVal = std::get<0>(b);
  int bType = std::get<1>(b);

  return (aVal < bVal) || (aVal == bVal && aType < bType);
}

int binary_search_inner(vector<tuple<int, int>> a, int x, int left, int right) {
  if(right < left) return -1;
  int mid = left+(right-left)/2;

  int v = std::get<0>(a[mid]);
  int type = std::get<1>(a[mid]);
  if(v == x) {
    if(type == START) left = mid + 1;
    else if(type == END) right = mid -1;
    else if(type == POINT) return mid;
  }
  else if(v < x) left = mid + 1;
  else if(v > x) right = mid -1;

  return binary_search_inner(a, x, left, right);
}

int binary_search(vector<tuple<int, int>> a, int x) {
  if(a.size() == 0) return -1;
  return binary_search_inner(a, x, 0, (int)a.size()-1);
}

int binary_search_last(vector<int> a, int x, int left, int right) {
  int mid = left+(right-left)/2;
  if(right < left) {
    while(a[mid] > x) mid--;
    return mid+1;
  }

  if(a[mid] == x) {
    while(mid < a.size() && a[mid+1] == x) ++mid;
    return mid+1;
  }
  if(a[mid] < x) left = mid + 1;
  if(a[mid] > x) right = mid -1;

  return binary_search_last(a, x, left, right);
}

int lower_or_equal_count(vector<int> a, int x) {
  if(a.size() == 0) return 0;
  if(x < a[0]) return 0;
  if(x > a[a.size()-1]) return a.size();
  return binary_search_last(a, x, 0, (int)a.size()-1);
}

vector<int> fast_count_segments2(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  vector<tuple<int, int>> weightedPoints(starts.size() + ends.size() + points.size());
  map<int, vector<int>> point_map;

  for(size_t i = 0; i < starts.size(); i++) {
    weightedPoints[i] = tuple<int, int>{starts[i], START};
    weightedPoints[starts.size()+i] = tuple<int, int>{ends[i], END};
  }
  for(size_t i = 0; i < points.size(); i++) {
    weightedPoints[starts.size()+ends.size()+i] = tuple<int, int>{points[i], POINT};
    point_map[points[i]].push_back(i);
  }

  std::sort(weightedPoints.begin(), weightedPoints.end(), sortWeightedPoint);

  int coverage = 0;
  for(size_t i = 0; i < weightedPoints.size(); i++) {
    int val = std::get<0>(weightedPoints[i]);
    int type = std::get<1>(weightedPoints[i]);
    if(type == START) coverage++;
    else if(type == END) coverage--;
    else if(type == POINT) {
      for(size_t j = 0; j < point_map[val].size(); j++)
        cnt[point_map[val][j]] = coverage;
    }
  }
  
  return cnt;
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> counts(points.size());

  std::sort(starts.begin(), starts.end());
  std::sort(ends.begin(), ends.end());

  for(size_t i = 0; i < points.size(); i++) 
    counts[i] = lower_or_equal_count(starts, points[i]) - lower_or_equal_count(ends, points[i]-1);

  return counts;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

void test_solution() {
  struct test {
    string title;
    vector<int> starts, ends, points, expected;
  };

  vector<test> tests = {
    {
      "sample 1",
      vector<int>{0, 7},
      vector<int>{5, 10},
      vector<int>{1, 6, 11},
      vector<int>{1, 0, 0},
    },
    {
      "sample 2",
      vector<int>{-10},
      vector<int>{10},
      vector<int>{-100, 100, 0},
      vector<int>{0, 0, 1},
    },
    {
      "sample 3",
      vector<int>{0, -3, 7},
      vector<int>{5, 2, 10},
      vector<int>{1, 6},
      vector<int>{2, 0},
    },
    {
      "empty",
      vector<int>{},
      vector<int>{},
      vector<int>{},
      vector<int>{},
    },
    {
      "single present",
      vector<int>{0},
      vector<int>{5},
      vector<int>{0},
      vector<int>{1},
    },
    {
      "start edge",
      vector<int>{0},
      vector<int>{0},
      vector<int>{0},
      vector<int>{1},
    },
    {
      "end edge",
      vector<int>{0},
      vector<int>{1},
      vector<int>{1},
      vector<int>{1},
    },
  };

  for(size_t i = 0; i < tests.size(); i++) {
    std::cout << "test: " << tests[i].title << std::endl;    
    vector<int> result = fast_count_segments2(tests[i].starts, tests[i].ends, tests[i].points);
    printIntVec(result);
    assert(result == tests[i].expected);
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments2(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
