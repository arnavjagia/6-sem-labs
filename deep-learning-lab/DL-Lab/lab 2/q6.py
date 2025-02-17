import torch

x = torch.tensor(3.0 ,requires_grad= True)
y = torch.tensor(4.0, requires_grad= True)
z = torch.tensor(5.0, requires_grad= True)

a = 2 * x
b = torch.sin(y)
c = a / b
d = c * z
e = torch.log(d + 1)
f = torch.tanh(e)
f.backward()
# can find gradient of leaf nodes in computational graphs only
print(x.grad, y.grad, z.grad)