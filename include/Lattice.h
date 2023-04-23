#ifndef LATTICE_H
#define LATTICE_H


// Variable

typedef struct Lattice{
	int NSite;
	double *Path;
} Lattice;

// Methods : pre-defined

int CreateLattice(Lattice*, int NSite);
void DestroyLattice(Lattice*);
int Initialize(Lattice*, double Min, double Max);
double Get(Lattice*, int Site);
void Set(Lattice*, int, double X);

// Methods : user-defined

typedef double SiteFunction(Lattice*, int Site, double *Parameter);


#endif