import torch
from torch import nn


class PE(nn.Module):

    def __init__(self, embed_dim, max_len=5000):
        super().__init__()
        # sin(position / 10000^{i//2*2 /dim}), cos()
        pe = torch.zeros(max_len, embed_dim)
        position = torch.arange(0, max_len, dtype=torch.float)[..., None]  # 升维
        item = 10000**(torch.arange(0, embed_dim, 2) / embed_dim)  # embed_dim//2
        pe[:, 0::2] = (position / item).sin()
        pe[:, 1::2] = (position / item).cos()
        self.pe = pe[None, ...]

    def forward(self, x):
        B, LEN, C = x.shape
        return self.pe[:, :LEN, :]


class MultiHeadAttention(nn.Module):

    def __init__(self, embed_dim, num_head):
        super().__init__()
        self.num_head = num_head
        self.head_dim = embed_dim // num_head

        self.query_linear = nn.Linear(embed_dim, embed_dim)
        self.value_linear = nn.Linear(embed_dim, embed_dim)
        self.key_linear = nn.Linear(embed_dim, embed_dim)

        self.output_linear = nn.Linear(embed_dim, embed_dim)

    def forward(self, query, key, value):
        B, LEN, C = query.shape
        B, NHW, C = key.shape

        Q = self.query_linear(query)
        K = self.key_linear(key)
        V = self.value_linear(value)

        Q = Q.view(B, LEN, self.num_head, self.head_dim).transpose(1, 2)
        K = K.view(B, NHW, self.num_head, self.head_dim).transpose(1, 2)
        V = V.view(B, NHW, self.num_head, self.head_dim).transpose(1, 2)

        attention = torch.softmax(torch.matmul(Q, K.transpose(-2, -1)) / self.head_dim**0.5, dim=-1)
        output = torch.matmul(attention, V).transpose(1, 2).contiguous().view(B, LEN, C)

        output = self.output_linear(output)
        return output, attention


class Decoder(nn.Module):

    def __init__(self, embed_dim, num_head, ffn_dim):
        super().__init__()
        self.self_attention = MultiHeadAttention(embed_dim, num_head)
        self.cross_attention = MultiHeadAttention(embed_dim, num_head)
        self.ffn = nn.Sequential(*[
            nn.Linear(embed_dim, ffn_dim),
            nn.ReLU(),
            nn.Dropout(0.1),
            nn.Linear(ffn_dim, embed_dim),
        ])
        self.layer_norm1 = nn.LayerNorm(embed_dim)
        self.dropout1 = nn.Dropout(0.1)
        self.layer_norm2 = nn.LayerNorm(embed_dim)
        self.dropout2 = nn.Dropout(0.1)
        self.layer_norm3 = nn.LayerNorm(embed_dim)
        self.dropout3 = nn.Dropout(0.1)

        self.init_query = nn.Parameter(torch.zeros(1, 100, embed_dim))
        self.pe_encoder = PE(embed_dim)

    def forward(self, query, memory):
        query_pos = self.pe_encoder(query)
        memory_pos = self.pe_encoder(memory)

        tgt, _ = self.self_attention(query + query_pos, query + query_pos, query)
        tgt = self.layer_norm1(query + self.dropout1(tgt))

        tgt1, _ = self.cross_attention(tgt + query_pos, memory + memory_pos, memory)
        tgt = self.layer_norm2(tgt + self.dropout2(tgt1))

        tgt2 = self.ffn(tgt)
        tgt = self.layer_norm3(tgt + self.dropout3(tgt2))

        return tgt


if __name__ == "__main__":
    batch_size = 1
    nhw = 200
    embed_dim = 256
    memory = torch.rand(batch_size, nhw, embed_dim)

    decoder = Decoder(embed_dim, 8, 1024)
    init_query = decoder.init_query
    output = decoder(init_query, memory)
    print(output)
