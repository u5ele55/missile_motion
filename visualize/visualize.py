from trajectory import *
from trasse import *
MAJOR_AXIS = 6378137; 
MINOR_AXIS = 6356752.3142; 

if __name__ == '__main__':
    window1 = plt.figure(1)
    ax = window1.add_subplot()
    trdr = TrajectoryDrawer(r"trajectory.txt")
    trdr.draw(ax)
    window1.canvas.manager.set_window_title("Trajectory")

    window2 = plt.figure(2)
    ax2 = window2.add_subplot()
    TrasseDrawer(r"trajectory.txt").draw(ax2)
    window2.canvas.manager.set_window_title("Trasse")
    plt.show()