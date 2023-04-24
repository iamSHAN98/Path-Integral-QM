# Path-Integral-QM

Monte-Carlo  path integral for non-relativistic quantum mechanics
numerically on a lattice

## Usage

### Compilation

Build the event generator binary `integral` using
the following command

```shell
make
```

### Event Generation

A [configuration](input/config) in plain ASCII is must be provided to the
event generator binary as an input

```shell
./integral input/config
```

This generates three outputs containing event ensembles of the
quantities calculated as weighted averages over path :

* Lattice.dat : space-time trajectories (paths) of particles

* Energy.dat : expectation value of the Hamiltonian operator

* Correlation.dat : expectation value of the 2-point correlator

### [Plotting](tool/README.md)