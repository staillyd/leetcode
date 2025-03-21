#include <algorithm>
#include <iostream>
#include <vector>

struct Bbox2d {
  Bbox2d(const float in_sx, const float in_sy, const float in_ex, const float in_ey, const float in_score)
      : sx(in_sx), sy(in_sy), ex(in_ex), ey(in_ey), score(in_score) {
    keep = true;
  }

  float area() { return (ex - sx + 1) * (ey - sy + 1); }

  void print() { std::cout << sx << ", " << sy << ", " << ex << ", " << ey << ", " << score << std::endl; }

  float sx;
  float sy;
  float ex;
  float ey;
  float score;
  bool keep;
};

float get_iou(Bbox2d box1, Bbox2d box2) {
  float left_x = std::max(box1.sx, box2.sx);
  float right_x = std::min(box1.ex, box2.ex);
  float top_y = std::max(box1.sy, box2.sy);
  float bottom_y = std::min(box1.ey, box2.ey);

  if (left_x > right_x || bottom_y < top_y) {
    return 0;
  }

  float intersection_area = (right_x - left_x + 1) * (bottom_y - top_y + 1);
  float union_area = box1.area() + box2.area() - intersection_area;
  return intersection_area / union_area;
}

void nms(std::vector<Bbox2d>& boxes) {
  const float iou_threshold = 0.3;

  std::sort(boxes.begin(), boxes.end(), [](const Bbox2d& lhs, const Bbox2d& rhs) { return lhs.score > rhs.score; });

  for (size_t i = 0; i < boxes.size(); ++i) {
    if (!boxes[i].keep) {
      continue;
    }
    for (size_t j = i + 1; j < boxes.size(); ++j) {
      if (!boxes[j].keep) {
        continue;
      }

      float iou = get_iou(boxes[i], boxes[j]);
      if (iou > iou_threshold) {
        boxes[j].keep = false;
      }
    }
  }

  boxes.erase(std::remove_if(boxes.begin(), boxes.end(), [](const Bbox2d& box) { return !box.keep; }), boxes.end());
}

int main(int argc, char const* argv[]) {
  std::vector<Bbox2d> boxes;
  boxes.emplace_back(Bbox2d(83.f, 54.f, 165.f, 163.f, 0.8));
  boxes.emplace_back(Bbox2d(67.f, 48.f, 118.f, 132.f, 0.5));
  boxes.emplace_back(Bbox2d(91.f, 38.f, 192.f, 171.f, 0.6));

  for (auto& box : boxes) {
    box.print();
  }

  nms(boxes);

  std::cout << "------------------" << std::endl;

  for (auto& box : boxes) {
    box.print();
  }

  return 0;
}
