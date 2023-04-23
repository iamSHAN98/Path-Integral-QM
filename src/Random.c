#include <math.h>

#include "mt64.h"
#include "Random.h"

double Uniform(double Min, double Max){
	double r = (Max - Min)*genrand64_real1();
  return r + Min;
}

double Linear(double Min, double Max){																		// Inverser sampling
	double r = genrand64_real1();
  return sqrt(r*(Max*Max - Min*Min) + Min*Min);
}

double Sine(double Period){																								// Inverse sampling
	double r = genrand64_real1();
	return acos(2*r - 1.)/Period;
}

double Gaussian(double Mean, double StdDev){															// Box-Muller transformation
	double th = 2*M_PI*genrand64_real1();
	double r = sqrt(-2*StdDev*StdDev*log(genrand64_real3()));
	return r*sin(th) + Mean;
}

double Exponential(double Rate){																					// Inverse sampling
	double u = genrand64_real1();
	return -log(1. - u)/Rate;
}