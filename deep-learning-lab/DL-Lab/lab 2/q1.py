import torch

a = torch.tensor(5.0, requires_grad= True)
b = torch.tensor(5.0, requires_grad= True)
x = (2 * a) + (3 * b)
y = (5 * (a ** 2)) + (3 * (b ** 3))
z = (2 * x) + (3 * y)
z.backward()
def manual(a, b):
    z_x, z_y = 2, 3
    x_a, y_a = 2, 10 * a
    return (z_x * x_a) + (z_y * y_a)
print(a.grad, manual(a, b))