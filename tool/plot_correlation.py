#!/usr/bin/env python3

import sys
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from parser import get_arguments, get_config

# Load configuration

args = get_arguments()
config = get_config(args.config)

# Load data

print("Reading from", args.input[0])
data = np.loadtxt(args.input[0])

# Histogram

corr_mean, corr_error = [], []
for i in range(config["NSite"] + 1) :
    step_data = data[i::config["NSite"] + 1]
    corr_mean.append(np.mean(step_data))
    corr_error.append(np.std(step_data))

max_time = config["NSite"]*config["Step"]
time = np.arange(0, max_time + config["Step"], config["Step"])
corr_th = 0.5*(np.exp(-time) + np.exp(-max_time)*np.exp(time))

# Formatting

mpl.rcParams['font.family'] = 'serif'                                     # Text font
mpl.rcParams['font.serif'] = 'DejaVu Serif'
mpl.rcParams['mathtext.fontset'] = 'dejavuserif'                          # Math font
mpl.rcParams['mathtext.default'] = 'regular'

# Plot

fig = plt.figure(1)
ax = fig.add_subplot(111)
	
ax.errorbar(time, corr_mean, yerr = corr_error, ls = "--", lw = 0., 
            marker = 'o', ms = 10, mew = 1.5, elinewidth = 1.,
            capsize = 5., color = 'r', mfc = 'none', mec = 'r',
            ecolor = 'r', label = r"Numerical")
ax.plot(time, corr_th, ls = '--', lw = 2., color = 'blue', label = "Analytical")

ax.set_xlabel(r"$\tau$ [arb]", size = 20, labelpad = 5)
ax.set_ylabel(r"$\langle \mathbb{X}(\tau) \mathbb{X}(0) \rangle$", size = 20,
              labelpad = 5)

ax.tick_params(axis = 'both', labelsize = 15)
ax.ticklabel_format(axis = 'both', style = 'sci', scilimits = (-3, 3),
                    useMathText = True)
ax.locator_params(axis = 'both', nbins = 5, integer = False)
ax.minorticks_off()

ax.legend(prop = {'size' : 15}, ncol = 1, framealpha = 1, loc = 'best')

info = r"$\alpha$ = %.1f" % (config["Potential"][0])
ax.text(0.425, 0.725, info, fontsize = 15, transform = ax.transAxes)

info = r"$\beta$ = %.1f" % (config["Potential"][1])
ax.text(0.425, 0.65, info, fontsize = 15, transform = ax.transAxes)

fig.tight_layout()
try :
  ext = args.output[0].split(".")[1]
  fig.savefig(args.output[0], format = ext, bbox_inches = 'tight',
                   pad_inches = 0.25)
except :
  plt.show()