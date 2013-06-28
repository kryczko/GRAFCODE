#!/usr/bin/env python

import os, sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.mlab import griddata

nooa = 64

f = open('esp_vs_yz.dat', 'r')

xcoords = []
ycoords = []
zcoords = []
electro = []

for line in f.readlines():
    y = float(line.split()[0])
    z = float(line.split()[1])
    esp = float(line.split()[2])

    ycoords.append(y)
    zcoords.append(z)
    electro.append(esp)	

plt.figure()

xlist = xcoords
ylist = ycoords               #np.linspace(-2., 1., 100)
zlist = zcoords               #np.linspace(-1., 1., 100)
esplist = electro

yi = np.linspace(0., 8.47, 100)
zi = np.linspace(0., 23.4, 100)

espi = griddata (ylist, zlist, esplist, yi, zi)

CS = plt.contour(yi,zi,espi,5,linewidths=0.5,colors='k')
CS = plt.contourf(yi,zi,espi,15,cmap=plt.cm.rainbow)
plt.colorbar()


#plt.title('Number of hydrogen bonds per molecule wrt y and z axis')
plt.xlabel('y-axis [Angstroms]')
plt.ylabel('z-axis [Angstroms]')

#plt.clabel(CS, inline=1, fontsize=10)
plt.show()

