#include <iostream>
#include <cassert>
#include <vector>
#include <assert.h>

using std::vector;

int binary_search_inner(const vector<int> &a, int x, int left, int right) {
  if(right < left) return -1;
  int mid = left+(right-left)/2;

//printf("left: %d, right: %d mid: %d\n", left, right, mid);

  if(a[mid] == x) return mid;
  if(a[mid] < x) left = mid + 1;
  if(a[mid] > x) right = mid -1;

  return binary_search_inner(a, x, left, right);
}

int binary_search(const vector<int> &a, int x) {
  if(a.size() == 0) return -1;
  return binary_search_inner(a, x, 0, (int)a.size()-1);
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

void test_solution() {
  assert(binary_search(vector<int>{}, 2) == -1);
  assert(binary_search(vector<int>{-1}, -1) == 0);
  assert(binary_search(vector<int>{1}, 1) == 0);
  assert(binary_search(vector<int>{1, 2}, 2) == 1);
  assert(binary_search(vector<int>{1, 2, 3}, 0) == -1);
  assert(binary_search(vector<int>{1, 2, 3, 4, 5, 6}, 1) == 0);
  assert(binary_search(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 6) == 5);
  assert(binary_search(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10) == 9);


  // dups
  assert(binary_search(vector<int>{1, 1}, 1) == 0);
  assert(binary_search(vector<int>{1, 1, 1}, 1) == 1);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    std::cout << binary_search(a, b[i]) << ' ';
  }
}
