#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

using std::vector;
using std::swap;


void printVec(std::vector<int> vec, int l, int r) {
  printf("[");
  for(size_t i = l; i <= r; i++) {
    printf(" %d ", vec[i]);
  }
  printf("]\n");
}

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

int partition3(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  int k = l;

  for (int i = l + 1; i <= r; i++) {
    if (a[i] < x) {
      j++;
      k++;
      swap(a[j], a[k]);
      swap(a[i], a[j]);
    }
    else if(a[i] == x) {
      k++;
      swap(a[i], a[k]);
    }
  }
  swap(a[l], a[j]);

  return j;
}

int hoarePartition(vector<int> &a, int l, int r) {
  int x=a[l],i=l-1,j=r+1;
  while (1) {
    do  j--; while (a[j] > x);
    do  i++; while (a[i] < x);
    if(i < j) 
      swap(a[i], a[j]);
    else 
      return j;
  }
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  int m = hoarePartition(a, l, r);

  randomized_quick_sort(a, l, m);
  randomized_quick_sort(a, m + 1, r);
}

void test_solution() {
  std::vector<int> vec;
    
  vec = vector<int>{2, 3, 9, 2, 2};
  randomized_quick_sort(vec, 0, 4);
  assert(vec == (vector<int>{2, 2, 2, 3, 9}));

  vec = vector<int>{2, 3};
  randomized_quick_sort(vec, 0, 1);
  assert(vec == (vector<int>{2, 3}));

  vec = vector<int>{3, 2};
  randomized_quick_sort(vec, 0, 1);
  assert(vec == (vector<int>{2, 3}));

  vec = vector<int>{3};
  randomized_quick_sort(vec, 0, 0);
  assert(vec == (vector<int>{3}));

  vec = vector<int>{3, 2, 2, 4, 5, 3, 4, 3, 3, 6, 7, 3, 5 ,3 ,3 ,4 ,5 ,3 ,3 ,3 };
  randomized_quick_sort(vec, 0, 19);
  printVec(vec, 0, 19);
  assert(vec == (vector<int>{2,2,3,3,3,3,3,3,3,3,3,3,4,4,4,5,5,5,6,7}));
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
