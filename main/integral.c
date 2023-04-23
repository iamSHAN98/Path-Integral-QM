#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Config.h"
#include "Random.h"
#include "Lattice.h"
#include "Kinematic.h"
#include "Operator.h"


double Potential(double X, double *Par){
	return 0.5*X*X + Par[0]*X*X*X + Par[1]*X*X*X*X;
}

double PotentialDerivative(double X, double *Par){
	return X + 3*Par[0]*X*X + 4*Par[1]*X*X*X;
}

double Hamiltonian(Lattice *Obj, int Site, double *Par){
	double X = Get(Obj, Site);

	double Pot = Potential(X, Par);
	double Kin = 0.5*X*PotentialDerivative(X, Par);

	return Kin + Pot;
}

double TwoPointCorrelator(Lattice *Obj, int Site, double *Par){
	int Index = (int)Par[0];
	double X1 = Get(Obj, Site), X2 = Get(Obj, Site + Index);
	return X2*X1;
}

void PrintBuffer(FILE *Stream, double *Buffer, int Length){
	int Index;
	for(Index = 0; Index < Length; Index++)
		fprintf(Stream, "%f\n", Buffer[Index]);
}


int main(int argc, char **argv){

	// Variables
	Lattice Obj;
	Parameter Config;
	PotentialFunction *FunctionPot;
	SiteFunction *FunctionHam, *FunctionCorr;


	// Load configuration
	if(argc	< 2){
		printf("Configuration not provided\n");
		return 1;
	}
	FILE *ConfigFile = fopen(argv[1], "r");	
	GetConfiguration(ConfigFile, &Config);
	// PrintConfiguration(&Config);


	// Initialize
	CreateLattice(&Obj, Config.NSite);														// Offset depends on stencil

	if(Config.HotStart)
		if(Initialize(&Obj, Config.LatticeRange[0], Config.LatticeRange[1]))
			exit(1);
	// PrintBuffer(stdout, Obj.Path, Config.NSite);

	FunctionPot = &Potential;
	FunctionHam = &Hamiltonian;
	FunctionCorr = &TwoPointCorrelator;


	// Simulation
	int Step, Iter, Site;
	double Energy;

	FILE *OutputLattice = fopen("Lattice.dat", "w");
	FILE *OutputEnergy = fopen("Energy.dat", "w");
	FILE *OutputCorrelation = fopen("Correlation.dat", "w");

	Energy = GetEnergy(&Obj, Config.Step, FunctionPot, Config.Potential);

	for(Step = 0; Step < Config.NThermalize + Config.NEvent; Step++){
		for(Iter = 0; Iter < Config.NSite;){

			Site = (int)Config.NSite*Uniform(0., 1.);														// Randomly pick a site
			double X = Get(&Obj, Site);

			double Shift = Uniform(-Config.ShiftMax, Config.ShiftMax);
			Set(&Obj, Site, X + Shift);
			double EnergyNew = GetEnergy(&Obj, Config.Step, FunctionPot, Config.Potential);

			if(exp(-(EnergyNew - Energy)/Config.HBar) > Uniform(0., 1.)){				// Metropolis test
				Energy = EnergyNew;
				Iter++;
			}
			else
				Set(&Obj, Site, X);

		}

		if(Step > Config.NThermalize - 1){																		// Output after thermalization
			PrintBuffer(OutputLattice, Obj.Path, Config.NSite);

			double MeanEnergy = GetAverage(&Obj, FunctionHam, Config.Potential);
			PrintBuffer(OutputEnergy, &MeanEnergy, 1);

			double Time, MeanCorrelation;
			for(Site = 0; Site < Config.NSite + 1; Site++){
				Time = (double)Site;
				MeanCorrelation = GetAverage(&Obj, FunctionCorr, &Time);
				PrintBuffer(OutputCorrelation, &MeanCorrelation, 1);
			}
		}

	}


	// Exit
	DestroyLattice(&Obj);
	fclose(ConfigFile);
	fclose(OutputLattice);
	fclose(OutputEnergy);
	fclose(OutputCorrelation);
	return 0;
}