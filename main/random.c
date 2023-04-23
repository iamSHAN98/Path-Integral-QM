#include <stdio.h>
#include <stdlib.h>

#include "Random.h"

int main(int argc, char **argv){

	int N = (argc > 1) ? atoi(argv[1]) : 1;
	printf("Generating %d random numbers\n\n", N);

	// --------------------------------------------------------------------- Input : distribution

	int Choice = 0;
	printf("Distributions :\n");
	printf("1. Uniform \n");
	printf("2. Linear \n");
	printf("3. Sine\n");
	printf("4. Gaussian\n");
	printf("5. Exponential\n");
	printf("Enter option : ");
	scanf("%d", &Choice);
	printf("\n");


	// --------------------------------------------------------------------- Input : parameters

	double ParA, ParB;
	switch(Choice){
		case 1 : printf("Enter minimum & maximum : ");
						 scanf("%lf %lf", &ParA, &ParB);
						 break;

		case 2 : printf("Enter minimum & maximum : ");
						 scanf("%lf %lf", &ParA, &ParB);
						 break;

		case 3 : printf("Enter frequency (2Pi x n) : ");
						 scanf("%lf", &ParA);
						 break;

		case 4 : printf("Enter mean & standard deviation : ");
						 scanf("%lf %lf", &ParA, &ParB);
						 break;

		case 5 : printf("Enter rate : ");
					   scanf("%lf", &ParA);
						 break;

		default : printf("No valid choice\n");
							exit(1);
	}


	// --------------------------------------------------------------------- Output

	FILE *File = fopen("random.dat", "w");

	int i;
	for(i = 0; i < N; i++){
		switch(Choice){
			case 1 : fprintf(File, "%lf\n", Uniform(ParA, ParB));
							 break;

			case 2 : fprintf(File, "%lf\n", Linear(ParA, ParB));
							 break;

			case 3 : fprintf(File, "%lf\n", Sine(ParA));
							 break;

			case 4 : fprintf(File, "%lf\n", Gaussian(ParA, ParB));
							 break;

			case 5 : fprintf(File, "%lf\n", Exponential(ParA));
							 break;
		}
	}
	
	fclose(File);
	return 0;

}