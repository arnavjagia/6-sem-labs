import torch

# check torch installation
print(torch.cuda.is_available())
print(torch.__version__)

# Creating different tensors
# Scalar tensor
scalar = torch.tensor(7)
print("Scalar tensor:", scalar)
print(scalar.item())  # get python number from tensor (applicable only for single-item tensors)

# Vector tensor
vector = torch.tensor(
    [7,7]
)
print("Vector:",vector)

# Matrix tensor
matrix = torch.tensor(
    [[7,8],
     [9,10]]
)
print("Matrix:",matrix)
print("Matrix Shape:",matrix.shape)

# Tensor
tensor = torch.tensor(
    [[[1,2,3],
      [3,6,9],
      [2,4,5]]]
)
print("Tensor:",tensor)
print("Tensor Dim:",tensor.ndim)

# Random Tensor
random_tensor = torch.rand(size=(3,4))
print((random_tensor,random_tensor.dtype))
