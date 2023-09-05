# This Python file uses the following encoding: utf-8
import sys
import numpy as np
import matplotlib.pyplot as plt
x = np.linspace(-3*np.pi,3*np.pi,100);
y = np.cos(x)
plt.plot(x,y)
plt.show()
print("cos1")

if __name__ == "__main__":
    print("cos2")
    print(sys.argv) # 终端可以传入参数 必须是单引号 python cos.py '123'
