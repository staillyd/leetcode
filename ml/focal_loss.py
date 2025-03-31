import torch
import torch.nn.functional as F
from torch import nn


class FocalLoss(nn.Module):

    def __init__(self, alpha=0.25, gamma=2, num_class=None, eps=1e-5):
        super().__init__()
        self.alpha = alpha
        self.gamma = gamma
        self.num_class = num_class
        self.eps = eps

    def forward(self, logits, target):
        if self.num_class is None or self.num_class == 1:  # 二分类
            prob = torch.sigmoid(logits)
            pt = prob * target + (1 - prob) * (1 - target)
        else:  # 多分类
            prob = torch.softmax(logits, dim=-1)
            target_onehot = F.one_hot(target, self.num_class)
            pt = (prob * target_onehot).sum(dim=-1)
        log_pt = (pt + self.eps).log()

        loss_all = -self.alpha * (1 - pt)**self.gamma * log_pt
        loss = loss_all.sum()
        return loss


if __name__ == "__main__":
    logits = torch.tensor([1.0, -1.0, 3.0, -3.0])
    target = torch.tensor([1, 0, 1, 0], dtype=torch.float32)

    loss_fn = FocalLoss()
    loss = loss_fn.forward(logits, target)
    print("Focal loss: ", loss.item())
