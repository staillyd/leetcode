import torch


def get_iou(box1, box2):
    sx1, sy1, ex1, ey1 = box1
    sx2, sy2, ex2, ey2 = box2

    x_min = torch.max(sx1, sx2)
    x_max = torch.min(ex1, ex2)
    y_min = torch.max(sy1, sy2)
    y_max = torch.min(ey1, ey2)

    if x_min > x_max or y_min > y_max:
        return 0

    intersection = torch.max(torch.tensor(0), (x_max - x_min + 1) * (y_max - y_min + 1))
    union = (ex1 - sx1 + 1) * (ey1 - sy1 + 1) - intersection
    return intersection / union


def nms(boxes, scores, iou_threshold=0.8):
    # boxes: (n, 4), score: (n, 1)
    idx = torch.argsort(scores, descending=True)
    boxes, scores = boxes[idx], scores[idx]

    keep = torch.tensor([True for _ in range(boxes.shape[0])])
    for i in range(boxes.shape[0]):
        if not keep[i]:
            continue
        for j in range(i + 1, boxes.shape[0]):
            if not keep[j]:
                continue
            iou = get_iou(boxes[i], boxes[j])
            if iou > iou_threshold:
                keep[j] = False

    return torch.where(keep == True)[0]


def get_ious(boxes):
    sx = torch.max(boxes[:, None, 0], boxes[:, 0])  # (n, n)
    sy = torch.max(boxes[:, None, 1], boxes[:, 1])
    ex = torch.min(boxes[:, None, 2], boxes[:, 2])
    ey = torch.min(boxes[:, None, 3], boxes[:, 3])

    intersection = (ex - sx + 1).clamp(0) * (ey - sy + 1).clamp(0)  # (n, n)
    area = (boxes[:, 2] - boxes[:, 0] + 1) * (boxes[:, 3] - boxes[:, 1] + 1)  # (n,)

    union = area[:, None] + area - intersection
    return intersection / union


def nms_batch(boxes, scores, iou_threshold=0.8):
    # boxes: (n, 4), score: (n, 1)
    idx = torch.argsort(scores, descending=True)
    boxes, scores = boxes[idx], scores[idx]

    keep = torch.tensor([True for _ in range(boxes.shape[0])])
    ious = get_ious(boxes)
    for i in range(boxes.shape[0]):
        if not keep[i]:
            continue
        for j in range(i + 1, boxes.shape[0]):
            if not keep[j]:
                continue

            if ious[i, j] > iou_threshold:
                keep[j] = False

    return torch.where(keep == True)[0]


if __name__ == "__main__":
    boxes = torch.tensor([[10, 10, 50, 50], [12, 12, 48, 48], [100, 100, 150, 150]])
    scores = torch.tensor([0.9, 0.8, 0.7])
    keep_idx = nms(boxes, scores, 0.3)
    print(keep_idx)

    keep_idx = nms_batch(boxes, scores, 0.3)
    print(keep_idx)
