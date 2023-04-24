#!/usr/bin/env python3

import sys
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from parser import get_arguments, get_config

# Load configuration

args = get_arguments()

# Load data

print("Reading from", args.input[0])
data = np.loadtxt(args.input[0])

count, center = np.histogram(data, bins = 100)
print("Mean :", np.mean(data), ", StdDev :", np.std(data))

# Formatting

mpl.rcParams['font.family'] = 'serif'                                     # Text font
mpl.rcParams['font.serif'] = 'DejaVu Serif'
mpl.rcParams['mathtext.fontset'] = 'dejavuserif'                          # Math font
mpl.rcParams['mathtext.default'] = 'regular'

# Plot

fig = plt.figure(1)
ax = fig.add_subplot(111)

ax.plot(center[:-1], count, ls = '-', lw = 2., color = 'blue', drawstyle = 'steps-mid')		
ax.fill_between(center[:-1], count, color = 'lightgrey', step = 'mid')

ax.set_xlabel("x [arb]", size = 20, labelpad = 5)
ax.set_ylabel("Counts", size = 20, labelpad = 5)

ax.tick_params(axis = 'both', labelsize = 15)
ax.ticklabel_format(axis = 'both', style = 'sci', scilimits = (-2, 2),
                    useMathText = True)
ax.locator_params(axis = 'both', nbins = 5, integer = False)
ax.minorticks_off()

fig.tight_layout()
plt.show()