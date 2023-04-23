#ifndef OPERATOR_H
#define OPERATOR_H

#include "Lattice.h"


// Methods : pre-defined

double GetAverage(Lattice *Obj, SiteFunction *Operator, double *Parameter){
	double Average = 0.;

	int Site;
	for(Site = 0; Site < Obj->NSite; Site++)
		Average += Operator(Obj, Site, Parameter);

	return Average/Obj->NSite;

}


#endif