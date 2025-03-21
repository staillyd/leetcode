#include <Eigen/Dense>
#include <iostream>
#include <random>
#include <vector>

struct Bbox2d {
  Bbox2d(float in_xmin, float in_xmax, float in_ymin, float in_ymax, float in_score)
      : xmin(in_xmin), xmax(in_xmax), ymin(in_ymin), ymax(in_ymax), score(in_score) {}

  void print() {
    std::cout << xmin << " " << xmax << " " << ymin << " " << ymax << " " << score << std::endl;
  }

  float area() const {
    return (xmax - xmin + 1) * (ymax - ymin + 1);
  }

  float xmin = 0.f, xmax = 0.f, ymin = 0.f, ymax = 0.f;
  float score = 0.f;
  bool keep = true;
};

float get_iou(const Bbox2d& box1, const Bbox2d& box2) {
  float xmin = std::max(box1.xmin, box2.xmin);
  float xmax = std::min(box1.xmax, box2.xmax);
  float ymin = std::max(box1.ymin, box2.ymin);
  float ymax = std::min(box1.ymax, box2.ymax);

  if (xmin > xmax || ymin > ymax) {
    return 0;
  }

  float intersection_area = (xmax - xmin + 1) * (ymax - ymin + 1);
  float union_area = box1.area() + box2.area() - intersection_area;

  return intersection_area / union_area;
}

void nms(std::vector<Bbox2d>& boxes) {
  std::sort(boxes.begin(), boxes.end(), [] (const Bbox2d& lhs, const Bbox2d& rhs) {return lhs.score > rhs.score;});

  for (size_t i = 0; i < boxes.size(); ++i) {
    if (!boxes[i].keep) {
      continue;
    }
    for (size_t j = i + 1; j < boxes.size(); ++j) {
      if (!boxes[j].keep) {
        continue;
      }

      float iou = get_iou(boxes[i], boxes[j]);
      if (iou > 0.5) {
        boxes[j].keep = false;
      }
    }
  }

  boxes.erase(std::remove_if(boxes.begin(), boxes.end(), [](const Bbox2d& b) {return !b.keep;}), boxes.end());
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
