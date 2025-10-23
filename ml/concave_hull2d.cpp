#include <eigen3/Eigen/Dense>
#include <stddef.h>
#include <stdint.h>

#include <algorithm>
#include <cmath>
#include <limits>
#include "segment2d.h" // 线段相关代码

typedef Eigen::Vector2d Vec2d;

class ConcaveHull2d {
 public:
  // Compute concave hull using iterative edge-insertion method.
  //  max_edge_len: any hull edge longer than this will be refined by inserting
  //  the nearest interior point. Smaller max_edge_len -> more concave detail.
  void ComputeConcaveHullByEdgeInsertion(const std::vector<Vec2d>& points,
                                         double max_edge_len);

  // Compute convex hull using Andrew's monotone chain algorithm. O(n log n)
  // This is similar to the existing Polygon2d::ComputeConvexHull but with
  // clearer implementation.
  void ComputeConvexHullByAndrew(const std::vector<Vec2d>& points);

 private:
  // Check if the line segments intersect.
  bool HasLineSegmentsIntersection(const std::vector<Vec2d>& points,
                                   size_t start, size_t mid, size_t end);

  // Remove collinear points on the contour: keep only corner points in
  // concave_hull_, and move removed points into inner_points_.
  void SimplifyContour();

 public:
  const std::vector<Vec2d>& convex_hull() const { return convex_hull_; }
  const std::vector<Vec2d>& concave_hull() const { return concave_hull_; }
  const std::vector<Vec2d>& inner_points() const { return inner_points_; }

 private:
  std::vector<Vec2d> convex_hull_;
  std::vector<Vec2d> concave_hull_;
  std::vector<Vec2d> inner_points_;

 private:
  static constexpr double kEps = 1e-5;
};


void ConcaveHull2d::SimplifyContour() {
  if (concave_hull_.size() < 3) {
    return;
  }

  std::vector<Vec2d> simplified;
  simplified.reserve(concave_hull_.size());

  const size_t n = concave_hull_.size();
  for (size_t i = 0; i < n; ++i) {
    const Vec2d& prev = concave_hull_[(i + n - 1) % n];
    const Vec2d& curr = concave_hull_[i];
    const Vec2d& next = concave_hull_[(i + 1) % n];

    const Vec2d v1 = curr - prev;
    const Vec2d v2 = next - curr;

    // If near-collinear, delete only when curr lies strictly between prev and
    // next on the same line (i.e., v1 and v2 point in the same direction).
    const double cross = v1.CrossProd(v2);
    if (std::abs(cross) <= 1e-5) {  // larger than 1e-9
      const double dot = v1.Dot(v2);
      if (dot > 0.0) {  // prev - curr - next aligned and curr is between
        inner_points_.emplace_back(curr);
        continue;
      }
    }
    simplified.emplace_back(curr);
  }

  concave_hull_.swap(simplified);
}

void ConcaveHull2d::ComputeConcaveHullByEdgeInsertion(
    const std::vector<Vec2d>& input_pts, double max_edge_len) {
  if (max_edge_len <= 0) {
    concave_hull_.clear();
    return;
  }

  // Convex hull as initial boundary, and get inner points.
  ComputeConvexHullByAndrew(input_pts);

  concave_hull_ = convex_hull_;

  // Repeatedly split long edges by inserting the nearest interior point that
  // does not cause self-intersection, until convergence.
  if (concave_hull_.size() < 3) {
    return;
  }

  bool updated = true;
  // Guard against infinite loops in worst-case degeneracies.
  int max_iterations = static_cast<int>(inner_points_.size()) * 4 + 16;
  while (updated && max_iterations-- > 0) {
    updated = false;
    if (concave_hull_.size() < 3 || inner_points_.empty()) {
      break;
    }

    const size_t n = concave_hull_.size();
    for (size_t i = 0; i < n; ++i) {
      const size_t j = (i + 1) % n;
      const Segment2d edge(concave_hull_[i], concave_hull_[j]);
      if (edge.length() <= max_edge_len) {
        continue;
      }

      // Find the nearest feasible inner point to this edge.
      double best_dist_sqr = std::numeric_limits<double>::infinity();
      size_t best_idx = static_cast<size_t>(-1);
      for (size_t k = 0; k < inner_points_.size(); ++k) {
        const Vec2d& candidate = inner_points_[k];
        const double dist_sqr = edge.DistanceSquareTo(candidate);

        // Quick reject by length: at least one of the two new edges should
        // be shorter than current edge to be meaningful.
        const double len1 = (candidate - concave_hull_[i]).Length();
        const double len2 = (candidate - concave_hull_[j]).Length();
        if (std::max(len1, len2) >= edge.length() - kEps) {
          continue;
        }

        // Build a tentative polygon with this point inserted between i and j
        // and test for self-intersection.
        std::vector<Vec2d> test_poly;
        test_poly.reserve(concave_hull_.size() + 1);
        for (size_t t = 0; t <= i; ++t) {
          test_poly.emplace_back(concave_hull_[t]);
        }
        test_poly.emplace_back(candidate);
        for (size_t t = i + 1; t < concave_hull_.size(); ++t) {
          test_poly.emplace_back(concave_hull_[t]);
        }

        if (HasLineSegmentsIntersection(test_poly, i,
                                        i + 1,  // inserted candidate index
                                        i + 2)) {
          continue;
        }

        if (dist_sqr < best_dist_sqr) {
          best_dist_sqr = dist_sqr;
          best_idx = k;
        }
      }

      if (best_idx != static_cast<size_t>(-1)) {
        // Insert the best candidate and remove from remaining inner points.
        const Vec2d chosen = inner_points_[best_idx];
        inner_points_.erase(inner_points_.begin() + best_idx);
        concave_hull_.insert(concave_hull_.begin() + (i + 1), chosen);
        updated = true;
        break;  // restart scanning edges from the beginning after insertion
      }
    }
  }

  SimplifyContour();
}

// https://oi-wiki.org/geometry/convex-hull/
void ConcaveHull2d::ComputeConvexHullByAndrew(
    const std::vector<Vec2d>& input_pts) {
  // sort and remove duplicate points
  std::vector<Vec2d> points = input_pts;
  std::sort(points.begin(), points.end(), [](const Vec2d& a, const Vec2d& b) {
    if (a.x() == b.x()) return a.y() < b.y();
    return a.x() < b.x();
  });
  points.erase(std::unique(points.begin(), points.end(),
                           [](const Vec2d& a, const Vec2d& b) {
                             return (std::abs(a.x() - b.x()) < kEps) &&
                                    (std::abs(a.y() - b.y()) < kEps);
                           }),
               points.end());

  std::vector<uint8_t> used(points.size(), 0);
  std::vector<size_t> indices;
  indices.reserve(points.size());
  // Build lower hull
  for (size_t i = 0; i < points.size(); ++i) {
    const auto& point = points[i];
    while (indices.size() >= 2) {
      const Vec2d& p1 = points[indices[indices.size() - 2]];
      const Vec2d& p2 = points[indices[indices.size() - 1]];
      double cross = (p2 - p1).CrossProd(point - p2);
      if (cross < -kEps) {
        used[indices[indices.size() - 1]] = 0;
        indices.pop_back();
      } else {
        break;
      }
    }
    if (i != 0) {  // for close contour, the first point is used
      used[i] = 1;
    }
    indices.emplace_back(i);
  }
  size_t lower_size = indices.size();

  // Build upper hull
  for (size_t i_inv = points.size(); i_inv > 0; --i_inv) {
    size_t i = i_inv - 1;
    if (used[i] == 1) {
      continue;
    }
    const auto& point = points[i];
    while (indices.size() > lower_size) {
      const Vec2d& p1 = points[indices[indices.size() - 2]];
      const Vec2d& p2 = points[indices[indices.size() - 1]];
      double cross = (p2 - p1).CrossProd(point - p2);
      if (cross < -kEps) {
        used[indices[indices.size() - 1]] = 0;
        indices.pop_back();
      } else {
        break;
      }
    }
    used[i] = 1;
    indices.emplace_back(i);
  }

  // Combine lower and upper hulls
  convex_hull_.clear();
  convex_hull_.reserve(indices.size());
  // as lower hull emplace back the first point but not used, skip index 0;
  // insert in reverse order
  for (size_t i_inv = indices.size(); i_inv > 1; --i_inv) {
    size_t i = i_inv - 1;
    convex_hull_.emplace_back(points[indices[i]]);
  }

  // Collect inner points
  inner_points_.clear();
  inner_points_.reserve(points.size() - convex_hull_.size());
  for (size_t i = 0; i < points.size(); ++i) {
    if (used[i] == 0) {
      inner_points_.emplace_back(points[i]);
    }
  }
}

bool ConcaveHull2d::HasLineSegmentsIntersection(
    const std::vector<Vec2d>& points, size_t start, size_t mid, size_t end) {
  const int n = static_cast<int>(points.size());
  if (n < 4) {
    return false;
  }

  const Segment2d test_edge_1(points[start], points[mid]);
  const Segment2d test_edge_2(points[mid], points[end]);

  auto next = [n](int idx) { return (idx + 1) % n; };
  auto shares_endpoint = [](int a1, int a2, int b1, int b2) {
    return a1 == b1 || a1 == b2 || a2 == b1 || a2 == b2;
  };

  for (int i = 0; i < n; ++i) {
    const int j = next(i);
    if (shares_endpoint(i, j, static_cast<int>(start), static_cast<int>(mid))) {
      continue;
    }
    if (shares_endpoint(i, j, static_cast<int>(mid), static_cast<int>(end))) {
      continue;
    }

    const Segment2d seg(points[i], points[j]);
    if (test_edge_1.HasIntersect(seg) || test_edge_2.HasIntersect(seg)) {
      return true;
    }
  }
  return false;
}

int main() {
  concave_hull2d = ConcaveHull2d();
  std::vector<Vec2d> points = {{1, 2}, {3, 4}, {2, 1}, {7, 3}, {5, 8}};
  concave_hull2d.ComputeConcaveHullByEdgeInsertion(points);

  const auto& convex_hull = concave_hull2d.convex_hull();
  const auto& concave_hull = concave_hull2d.concave_hull();
  const auto& inner_points = concave_hull2d.inner_points();

  return 0;
}