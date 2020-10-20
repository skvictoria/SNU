from matplotlib import pyplot as plt
import numpy as np
R =1*10**6
C =1*10**(-6)

tf = 10
delta = 0.5
N = (int)(tf/delta)
alpha = 1/(1+delta)
t = np.array([])
y_true = np.zeros(N)
y_sim = np.zeros(N)

for i in range(1,N):
y_sim[i] = alpha*y_sim[i-1] +(1-alpha)*1
t = i*delta
y_true[i] = 1 - np.exp(-t / (R * C))

plt.figure()
plt.plot(y_true,'r')
plt.plot(y_sim,'b')
plt.xlabel('Sampling')
plt.ylabel('Voltage')
plt.grid()
plt.title('blue: simulation, red : real')
plt.show()
