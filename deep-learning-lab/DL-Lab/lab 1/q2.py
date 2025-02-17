import torch

# permute helps permuting the shape of tensor
a = torch.rand(size=(3, 4))
print(a)
# can be used for transpose
a = torch.permute(a, dims=(1, 0))
print(a)