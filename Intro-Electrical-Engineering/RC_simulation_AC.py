from matplotlib import pyplot as plt
import numpy as np
import math
R =1*10**6
C =1*10**(-6)
w = 8*np.pi
tf = 10
delta = 0.1
theta = math.atan2(w*R*C,1)
N = (int)(tf/delta)
alpha = 1/(1+delta)
#t = np.array([])
y_true = np.zeros(N)
y_sim = np.zeros(N)
dif = np.zeros(N)
for i in range(1,N):
    t = i * delta
    y = (-1 / (1 + (w * R * C) ** 2) ** 0.5) * np.exp(-t / (R * C))
    y_true[i] = (1 / (1 + (w * R * C) ** 2) ** 0.5) * np.cos((w * t - theta)) + y
    y_sim[i] = alpha*y_sim[i-1] +(1-alpha)*np.cos(w*t)
    dif[i] = (y_true[i]-y_sim[i])**2
print(np.sum(dif))
plt.figure()
plt.plot(y_true,'r')
plt.plot(y_sim,'b')
plt.xlabel('Sampling')
plt.ylabel('Voltage')
plt.grid()
plt.title('blue: simulation, red : real')
plt.show()
