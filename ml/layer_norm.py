import torch
from torch import nn


class LayerNorm(nn.Module):

    def __init__(self, shape, eps=1e-5):
        super().__init__()
        self.gamma = nn.Parameter(torch.ones(shape))
        self.beta = nn.Parameter(torch.zeros(shape))

        self.eps = eps

    def forward(self, x):
        dim = tuple(range(-len(self.gamma.shape), 0))
        x_mu = x.mean(dim=dim, keepdim=True)  # (b, c, 1, 1)
        x_var = x.var(dim=dim, keepdim=True, unbiased=False)  # (b, c, 1, 1)

        x_hat = (x - x_mu) / (x_var + self.eps).sqrt()  # (b, c, h, w)

        return self.gamma * x_hat + self.beta  # 自动广播, 不像bn, 维度为1的不连续, 需要手动view


if __name__ == "__main__":
    N, C, H, W = 4, 3, 5, 5  # batch, channels, height, width
    x = torch.randn(N, C, H, W)  # 随机输入

    ln = LayerNorm((H, W))  # 在h,w上归一化
    output = ln.forward(x)
    print(output.shape)  # 应该仍然是 (N, C, H, W)
