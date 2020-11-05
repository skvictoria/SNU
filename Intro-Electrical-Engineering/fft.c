import numpy as np
from IPython.display import Audio, display
import matplotlib.pyplot as plt
%matplotlib qt5
from scipy.fftpack import fft

def sound_process(frequecy, sampling_rate=44100, how_much_time=3):
    t = np.linspace(0, how_much_time, how_much_time*int(sampling_rate))
    y = np.sin(2 * np.pi * frequecy * t)
    return y

do = sound_process(261.62)
mi = sound_process(329.62)
sol = sound_process(391.98)
harmony = do+mi+sol

plt.plot(harmony[:10000])
plt.show()

display(Audio(harmony, rate=44100))

yf = fft(harmony[:100000])

plt.plot(abs(yf))
plt.show()
