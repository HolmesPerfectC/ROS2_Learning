import numpy as np
a = np.zeros([3, 4])
print(a.shape)
for i, ele in enumerate(a):
    print(i)
    print(ele.shape)