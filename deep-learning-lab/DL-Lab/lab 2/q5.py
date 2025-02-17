import torch

x = torch.tensor(3.0, requires_grad= True)
y = (8 * (x ** 4)) + (3 * (x ** 3)) + (7 * (x ** 2)) + (6 * x) + 3
y.backward()

def manual(x):
    y_x = (32 * (x ** 3)) + (9 * (x ** 2)) + (14 * (x)) + 6
    return y_x

print(x.grad, manual(x))