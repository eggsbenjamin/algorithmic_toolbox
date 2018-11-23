#include <iostream>
#include <vector>
#include <assert.h>

using std::vector;

int merge(int *a, int low, int mid, int high) {
  int i = low;
  int j = mid+1;
  int k = 0;
  int tmp[high-low+1];
  int count = 0;

  while(i <= mid && j <= high) {
    if(a[i] <= a[j]) {
      tmp[k++] = a[i++];
    } else {
      tmp[k++] = a[j++];
      count += j-low-k;
    }
  }

  while(i <= mid) tmp[k++] = a[i++];
  while(j <= high) tmp[k++] = a[j++];
  for(i = low; i <= high; i++) a[i] = tmp[i-low];

  return count;
}

int merge_sort(int* a, int low, int high) {
  if(low >= high) return 0;

  int mid = (low+high)/2;
  return merge_sort(a, low, mid) + merge_sort(a, mid+1, high) + merge(a, low, mid, high);
}


void test_solution() {
  struct test {
    std::string title;
    vector<int> input;
    int expected;
  };

  vector<test> tests = {
    {
      "example 1",
      vector<int>{2, 3, 9, 2, 9},
      2,
    },
    {
      "example 2",
      vector<int>{2, 4, 1, 3, 5},
      3,
    },
    {
      "empty",
      vector<int>{},
      0,
    },
    {
      "single",
      vector<int>{1},
      0,
    },
    {
      "sorted asc",
      vector<int>{1, 2, 3, 4, 5},
      0,
    },
    {
      "sorted desc",
      vector<int>{5, 4, 3, 2, 1},
      (5*(5-1))/2,
    },
  };

  for(size_t i = 0; i < tests.size(); i++) {
    std::cout << "test: " << tests[i].title << std::endl;
    int result = merge_sort(&tests[i].input[0], 0, tests[i].input.size()-1);
    std::cout << "result: " << result << " expected: " << tests[i].expected << std::endl;
    assert(result == tests[i].expected);
  }
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << merge_sort(&a[0], 0, a.size()-1) << '\n';
}
