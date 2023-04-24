# Plotting Scripts

Each plotting script follows a general syntax for usage

```shell
./script.py --config /path/to/configuration --input /path/to/data --output /path/to/plot
```

or, use the corresponding [shorthand notations](parser.py) `-c`,
`-i` and `-o` for passing command line arguments. Event
ensemble output from the Monte-Carlo sampler is fed as
input to these scripts along with the specific input
used for event generation. 3 scripts are provided here

* `plot_ground_state.py` : plots ground state probability
  using `Lattice.dat`

* `plot_correlation.py` : plots 2-point correlator vs time
  using `Correlation.dat`

* `plot_excitation.py` : plots excitation energy for first
  excited state using `Correlation.dat`

* `plot_random.py` : plots distribution from an ensemble,
  mean and standard deviation for the same are printed. Use
  this to get the ground state energy from `Energy.dat`

*Analytic expressions for quantum harmonic oscillator are
also provided for reference comparison.*