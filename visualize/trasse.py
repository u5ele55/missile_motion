
import matplotlib.pyplot as plt
import numpy as np

class TrasseDrawer:
    def __init__(self, trasseFilename):
        self.fileTrasse = open(trasseFilename, 'r')

    def prepareTrasse(self):
        self.drawTrasse = True

    def draw(self, ax):
        data = self.fileTrasse.read().split('\n')
        xd,yd,zd = [], [], []
        
        for c in data[:-1]:
            x,z,y = [float(a) for a in c.strip('[]').split()]
            xd.append(x)
            yd.append(y)
            zd.append(z)
        xd = np.array(xd) / 1000
        yd = np.array(yd)
        zd = np.array(zd) / 1000
        ax.set_xlabel("distance, km")
        ax.set_ylabel("deviation, m")
        ax.scatter(xd[0], yd[0], label='Start', c='#FFFF00')

        ax.plot(xd, yd)
