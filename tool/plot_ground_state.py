#!/usr/bin/env python3

import sys
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from parser import get_arguments, get_config

# Load configuration

args = get_arguments()
config = get_config(args.config)

# Constants

xmax = 5.
nbin = 1000
dx = 2*xmax/nbin

# Load data

print("Reading from", args.input[0])
data = np.loadtxt(args.input[0])

# Histogram

proba, edge = np.histogram(data, bins = nbin, range = (-xmax, xmax), density = True)
center = 0.5*(edge[1:] + edge[:-1])

print("Total probability :", np.sum(proba)*dx)
print("Mean :", np.sum(proba*center)*dx)

proba_th = np.exp(-center*center/config['NSite'])/np.sqrt(np.pi)

# Formatting

mpl.rcParams['font.family'] = 'serif'                                     # Text font
mpl.rcParams['font.serif'] = 'DejaVu Serif'
mpl.rcParams['mathtext.fontset'] = 'dejavuserif'                          # Math font
mpl.rcParams['mathtext.default'] = 'regular'

# Plot

fig = plt.figure(1)
ax = fig.add_subplot(111)

ax.plot(center, proba, ls = '-', lw = 2., color = 'blue',
        drawstyle = 'steps-mid', label = "Numerical")		
ax.fill_between(center, proba, color = 'lightgrey', step = 'mid')

ax.plot(center, proba_th, ls = '--', lw = 2., color = 'red',
        label = "Analytical")

ax.set_xlabel("x [arb]", size = 20, labelpad = 5)
ax.set_ylabel(r"$\vert \psi_0 (x) \vert^2$", size = 20, labelpad = 5)

ax.tick_params(axis = 'both', labelsize = 15)
ax.ticklabel_format(axis = 'both', style = 'sci', scilimits = (-2, 2),
                    useMathText = True)
ax.locator_params(axis = 'both', nbins = 5, integer = False)
ax.minorticks_off()

ax.legend(prop = {'size' : 15}, ncol = 1, framealpha = 1, loc = 'upper right')

info = r"$\alpha$ = %.1f" % (config["Potential"][0])
ax.text(0.725, 0.725, info, fontsize = 15, transform = ax.transAxes)

info = r"$\beta$ = %.1f" % (config["Potential"][1])
ax.text(0.725, 0.65, info, fontsize = 15, transform = ax.transAxes)

fig.tight_layout()
try :
  ext = args.output[0].split(".")[1]
  fig.savefig(args.output[0], format = ext, bbox_inches = 'tight',
                   pad_inches = 0.25)
except :
  plt.show()