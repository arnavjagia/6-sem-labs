import torch

# creating tensors
a = torch.tensor(5)
print(a)

# check number of dimensions of a tensor
# note that since the tensor is just an array, the ndim is 1
b = torch.tensor([1, 1])
print(b.ndim)

# random tensors
a = torch.rand(size=(3, 4))
print(a, a.dtype)

# shape of tensor
print(a.shape)

# zeros tensor gives float tensor
a = torch.zeros(size=(3, 4))
print(a)

# ones tensor gives float tensor
a = torch.ones(size=(3, 4))
print(a)

# range creation; note datatype is still int
a = torch.arange(1, 10, 2)
print(a)

# creating a tensor full of zeros of another tensor's shape
# note that initally a had float datatype; after zeros_like it became int
a = torch.zeros_like(a)
print(a)