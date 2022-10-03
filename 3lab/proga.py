import numpy as np
import matplotlib.pyplot as plt

n = 1000
x = np.arange(0, n, 1.0)
SegmentState = np.arange(0, n, 1.0)
SetState = np.arange(0, n, 1.0)


for i in range(n):
    SegmentState[i] = float(input())
    SetState[i] = float(input())



fig, ax = plt.subplots()
ax.scatter(x, SegmentState, 6, label = 'SegmentState')
ax.scatter(x, SetState, 6, label = 'SetState')
ax.legend()
ax.set_xlabel('Граница')
ax.set_ylabel('Вероятность')
plt.text(100, 0.113, r'$seed = 50$')
plt.savefig('50.png')
plt.show()
