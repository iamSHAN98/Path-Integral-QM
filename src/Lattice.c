#include <stdio.h>
#include <stdlib.h>

#include "Random.h"
#include "Lattice.h"


int CreateLattice(Lattice *Obj, int NSite){
	if(Obj->Path){
		printf("Path already exists, can not re-create\n");
		return 1;
	}

	if(NSite <= 0){
		printf("%d is not a valid choice for number of sites\n", Obj->NSite);
		return 1;
	}

	Obj->Path = (double*)calloc(NSite, sizeof(double));
	Obj->NSite = NSite;

	return 0;
}

void DestroyLattice(Lattice *Obj){
	if(Obj->Path){
		free(Obj->Path);
		Obj->Path = NULL;
	}
}

int Initialize(Lattice *Obj, double Min, double Max){
	if(!Obj->Path){
		printf("Path does not exist, can not initialize\n");
		return 1;
	}

	int Site;
	for(Site = 0; Site < Obj->NSite; Site++)
		Obj->Path[Site] = Uniform(Min, Max);

	return 0;
}

double Get(Lattice *Obj, int Site){
	return Obj->Path[Site % Obj->NSite];													// Periodic boundary condition
}

void Set(Lattice *Obj, int Site, double X){
	Obj->Path[Site % Obj->NSite] = X;
}