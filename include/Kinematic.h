#ifndef KINEMATIC_H
#define KINEMATIC_H

#include "Lattice.h"


// Methods : user defined

typedef double PotentialFunction(double, double*);

// Methods : pre-defined

double PositionFunctional(Lattice *Obj, int Site){
	return 0.5*(Get(Obj, Site) + Get(Obj, Site + 1));
}

double MomentumFunctional(Lattice *Obj, int Site, double dT){
	return (Get(Obj, Site + 1) - Get(Obj, Site))/dT;
}

double GetEnergy(Lattice *Obj, double dT, PotentialFunction *Potential, double *Parameter){
	double Energy = 0.;

	int Site;
	for(Site = 0; Site < Obj->NSite; Site++){
		double Position = PositionFunctional(Obj, Site);
		double Momentum = MomentumFunctional(Obj, Site, dT);
		Energy += 0.5*Momentum*Momentum + Potential(Position, Parameter);
	}

	return Energy*dT;
}


#endif