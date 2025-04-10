#include <iostream>

class Solution {
 public:
  int remove_duplicates(int arr[], int len) {
    int slow = 0;
    for (int i = 1; i < len; ++i) {
      if (arr[i] != arr[slow]) {
        ++slow;
        arr[slow] = arr[i];
      }
    }
    return slow + 1;
  }
};

int main() {
  int a[6] = {1, 1, 1, 2, 2, 3};

  Solution solution = Solution();
  int len = solution.remove_duplicates(a, 6);
  for (int i = 0; i < len; ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
}