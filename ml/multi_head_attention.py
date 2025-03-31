import torch
from torch import nn


class MultiHeadAttention(nn.Module):

    def __init__(self, embed_dim, num_heads):
        super().__init__()
        self.embed_dim = embed_dim
        self.num_heads = num_heads
        self.head_dim = self.embed_dim // self.num_heads

        self.query_linear = nn.Linear(embed_dim, embed_dim)
        self.key_linear = nn.Linear(embed_dim, embed_dim)
        self.value_linear = nn.Linear(embed_dim, embed_dim)

        self.output_linear = nn.Linear(embed_dim, embed_dim)

    def forward(self, query, key, value):
        B, N, HW, C = value.shape
        B, M, C = query.shape

        Q = self.query_linear(query)
        K = self.key_linear(key)
        V = self.value_linear(value)

        Q = Q.view(B, M, self.num_heads, self.head_dim).transpose(1, 2)
        K = K.view(B, N * HW, self.num_heads, self.head_dim).transpose(1, 2)  # 上升维度, 外层for
        V = V.view(B, N * HW, self.num_heads, self.head_dim).transpose(1, 2)

        attention = torch.softmax(torch.matmul(Q, K.transpose(-2, -1)) / self.head_dim**0.5, dim=-1)
        output = torch.matmul(attention, V)

        output = output.transpose(1, 2).contiguous().view(B, M, C)
        output = self.output_linear(output)
        return output, attention

    def forward_split(self, query, key, value):
        # M->M_S
        B, N, HW, C = value.shape
        B, M, C = query.shape
        S = 2

        Q = self.query_linear(query)
        K = self.key_linear(key)
        V = self.value_linear(value)

        Q = Q.view(B * S, M // S, self.num_heads, self.head_dim).transpose(1, 2)
        idx = torch.randint(0, N, (1, 2))  # 从N中随机选2个
        K = K.gather(1, idx[..., None, None].expand(B, -1, HW, C))[None, ...].expand(S, -1, -1, -1, -1).contiguous()
        K = K.view(B * S, 2 * HW, self.num_heads, self.head_dim).transpose(1, 2)
        V = V.gather(1, idx[..., None, None].expand(B, -1, HW, C))[None, ...].expand(S, -1, -1, -1, -1).contiguous()
        V = V.view(B * S, 2 * HW, self.num_heads, self.head_dim).transpose(1, 2)

        attention = torch.softmax(torch.matmul(Q, K.transpose(-2, -1)) / self.head_dim**0.5, dim=-1)
        output = torch.matmul(attention, V)

        output = output.transpose(1, 2).contiguous().view(B * S, M // S, C).view(B, M, C)
        return output, attention


if __name__ == "__main__":
    embed_dim = 16
    num_head = 4
    batch_size = 2
    seq_len = 6
    hw = 300
    n = 7

    multi_head_attention = MultiHeadAttention(embed_dim, num_head)

    query = torch.rand(batch_size, seq_len, embed_dim)
    key = torch.rand(batch_size, n, hw, embed_dim)
    value = key

    output, attn = multi_head_attention(query, key, value)

    print("output dim:", output.shape)
    print("attn dim:", attn.shape)

    output2, attn2 = multi_head_attention.forward_split(query, key, value)
