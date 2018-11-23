#include <algorithm>
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

using std::vector;

// this passes the grader but is not a divde and conquer solution...
int get_majority_element(vector<int> a) {
  if(a.size() == 0) return -1;
  if(a.size() == 1) return a[0];

  sort(a.begin(), a.end());

  int minMaj = a.size()/2+1;
  for(int i = 0; i < minMaj; i++) {
    if(a[i] == a[i+minMaj-1]) return a[i];
  }

  return -1;
}

void test_solution() {
  // majority
  assert(get_majority_element(vector<int>{1}) == 1);
  assert(get_majority_element(vector<int>{1, 2, 2}) == 2);
  assert(get_majority_element(vector<int>{1, 1, 1, 2, 2, 2, 2}) == 2);
  assert(get_majority_element(vector<int>{1, 1, 1, 1, 2, 2, 2}) == 1);
  assert(get_majority_element(vector<int>{1, 1, 2, 2, 2, 2, 2, 1, 1}) == 2);

  // no majority
  assert(get_majority_element(vector<int>{1, 2}) == -1);
  assert(get_majority_element(vector<int>{1, 2, 3, 4}) == -1);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a) != -1) << '\n';
}
