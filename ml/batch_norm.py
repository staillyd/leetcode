import torch
from torch import nn


class BatchNorm(nn.Module):

    def __init__(self, C, eps=1e-5, lamb=0.9):
        super().__init__()
        self.gamma = nn.Parameter(torch.ones(C))  # 需要学习的参数
        self.beta = nn.Parameter(torch.zeros(C))  # 需要学习的参数

        self.eps = eps

        self.lamb = lamb
        self.running_mu = torch.zeros(C)  # 推理时用
        self.running_var = torch.ones(C)  # 推理时用

    def forward(self, x):
        # x: (n, c, h, w)
        if self.training:
            x_mu = x.mean(dim=(0, 2, 3), keepdim=True)  # (1, c, 1, 1)
            x_var = x.var(dim=(0, 2, 3), keepdim=True, unbiased=False)  # (1, c, 1, 1)
            x_hat = (x - x_mu) / (x_var + self.eps).sqrt()  # (n, c, h, w)

            self.running_mu = self.lamb * self.running_mu + (1 - self.lamb) * x_mu.flatten()
            self.running_var = self.lamb * self.running_var + (1 - self.lamb) * x_var.flatten()
        else:
            x_hat = (x - self.running_mu.view(1, -1, 1, 1)) / (self.running_var.view(1, -1, 1, 1) + self.eps).sqrt()
        return self.gamma.view(1, -1, 1, 1) * x_hat + self.beta.view(1, -1, 1, 1)


if __name__ == "__main__":
    N, C, H, W = 4, 3, 5, 5  # batch, channels, height, width
    x = torch.randn(N, C, H, W)  # 随机输入

    bn = BatchNorm(C)  # 保留C, 在其他维度归一化
    bn.train()
    output = bn.forward(x)
    print(output.shape)  # 应该仍然是 (N, C, H, W)

    bn.eval()
    output = bn.forward(x)

    print(output.shape)  # 应该仍然是 (N, C, H, W)
