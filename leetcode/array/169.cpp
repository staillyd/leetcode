#include <iostream>

class Solution {
 public:
  int majority_element(int arr[], int len) {
    int major = arr[0];
    int count = 0;
    for (int i = 0; i < len; ++i) {
      if (count == 0) {
        major = arr[i];
      }

      if (major == arr[i]) {
        ++count;
      } else {
        --count;
      }
    }
    return major;
  }
};

int main() {
  int a[7] = {1, 1, 1, 2, 2, 1, 2};

  Solution solution = Solution();
  int major = solution.majority_element(a, 7);
  std::cout << "major: " << major << std::endl;
}