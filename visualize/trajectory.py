
import matplotlib.pyplot as plt
import numpy as np

class TrajectoryDrawer:
    def __init__(self, trajectoryFilename):
        self.fileTrajectory = open(trajectoryFilename, 'r')

    def draw(self, ax):
        data = self.fileTrajectory.read().split('\n')
        xd,yd,zd = [], [], [] # ECEF
        
        for c in data[:-1]:
            x,z,y = [float(a) for a in c.strip('[]').split()]
            xd.append(x)
            yd.append(y)
            zd.append(z)
        xd = np.array(xd) / 1000
        yd = np.array(yd) / 1000
        zd = np.array(zd) / 1000
        ax.set_xlabel("distance, km")
        ax.set_ylabel("height, km")
        ax.plot(xd, zd, c='#0000FF')
        # ECI trajectory
        # ax.plot(xs, ys, zs, label='SC trajectory eci', c='#FF0000')
        ax.scatter(xd[0], zd[0], label='Start', c='#FFFF00')
        
        

#ax.plot(xs, ys, zs, label='SC trajectory eci')
