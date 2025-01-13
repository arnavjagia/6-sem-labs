import torch

# 1
# reshaping
tensor = torch.tensor(
    [[1,2,3],
      [3,6,9],
      [2,4,5],
      [4,5,2]]
)
if torch.cuda.is_available():
    tensor = tensor.to("cuda")
reshaped_tensor = torch.reshape(tensor, (2, 6))

print(f"Tensor: {tensor}\nReshaped Tensor: {reshaped_tensor}")

# viewing
view_tensor = tensor.view(4, 3)
print(view_tensor)