#include <iostream>

class Solution {
 public:
  int find_repeat_number(int arr[], int len) {
    for (int i = 0; i < len; ++i) {
      while (i != arr[i]) {
        if (arr[i] == arr[arr[i]]) {
          return arr[i];
        } else {
          std::swap(arr[i], arr[arr[i]]);
        }
      }
    }
    return -1;
  }
};

int main() {
  int a[6] = {1, 5, 0, 2, 2, 3};

  Solution solution = Solution();
  std::cout << "repeat num: " << solution.find_repeat_number(a, 6) << std::endl;
}