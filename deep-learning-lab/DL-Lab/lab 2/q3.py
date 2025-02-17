import torch

x = torch.tensor(3.0, requires_grad= True)
b = torch.tensor(4.0, requires_grad= True)
w = torch.tensor(5.0, requires_grad= True)
u = w * x
v = u + b
a = torch.sigmoid(v)
a.backward()

def manual(x, b, w):
    u = w * x
    v = u + b
    a = torch.sigmoid(v)
    a_v = a * (1 - a)
    v_u = 1
    u_w = x
    return a_v * v_u * u_w

print(w.grad, manual(x, b, w))