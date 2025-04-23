#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Solution {
 public:
  enum class Direction { left = 0, right, up, down };
  void spiral_order(const std::vector<std::vector<int>>& v) {
    int sx = 0, ex = v.size() - 1, sy = 0, ey = v[0].size() - 1;
    std::ostringstream oss;
    Direction dir = Direction::right;
    while (sx <= ex && sy <= ey) {
      if (dir == Direction::right) {
        for (int i = sx; i <= ex; ++i) {
          oss << v[sy][i] << " ";
        }
        dir = Direction::down;
        ++sy;
      } else if (dir == Direction::down) {
        for (int i = sy; i <= ey; ++i) {
          oss << v[i][ex] << " ";
        }
        dir = Direction::left;
        --ex;
      } else if (dir == Direction::left) {
        for (int i = ex; i >= sx; --i) {
          oss << v[ey][i] << " ";
        }
        dir = Direction::up;
        --ey;
      } else {
        for (int i = ey; i >= sy; --i) {
          oss << v[i][sx] << " ";
        }
        dir = Direction::right;
        ++sx;
      }
    }
    std::cout << oss.str() << std::endl;
  }
};

int main() {
  std::vector<std::vector<int>> a = {{0, 1, 2, 3}, {11, 12, 13, 4}, {10, 15, 14, 5}, {9, 8, 7, 6}};

  Solution solution = Solution();
  solution.spiral_order(a);
}