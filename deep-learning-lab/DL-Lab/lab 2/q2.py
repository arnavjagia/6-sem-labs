import torch

x = torch.tensor(3.0, requires_grad= True)
b = torch.tensor(4.0, requires_grad= True)
w = torch.tensor(5.0, requires_grad= True)
u = w * x
v = u + b
a = torch.relu(v)
a.backward()
print(w.grad)