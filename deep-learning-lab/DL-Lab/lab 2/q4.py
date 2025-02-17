import torch

x = torch.tensor(3.0, requires_grad= True)
a = -(x ** 2) - (2 * x) - torch.sin(x)
f = torch.exp(a)
f.backward()

def manual(x):
    a = -(x ** 2) - (2 * x) - torch.sin(x)
    f = torch.exp(a)
    a_x = (-2 * x) - 2 - torch.cos(x)
    a_x *= f
    return a_x

print(x.grad, manual(x))