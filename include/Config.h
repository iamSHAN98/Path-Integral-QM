#ifndef CONFIG_H
#define CONFIG_H


#include <string.h>

typedef struct Parameter{

	int NSite, NThermalize, NEvent;

	int HotStart;
	double LatticeRange[2];

	double ShiftMax;
	double Step, HBar;

	int NPot; double Potential[10];

} Parameter;


void GetConfiguration(FILE *ConfigFile, Parameter *Config){
	char Line[256], Key[256], Value[256];

	while(!feof(ConfigFile)){
		fgets(Line, 256, ConfigFile);

		if(Line[0] == '#') continue;																							 // Ignore comments
		if((Line[0] == '\n') || (Line[0] == '\t') || (Line[0] == ' ')) continue;	 // Ignore blank lines

		sscanf(Line, "%s %[^\n]", Key, Value);																		 // Read key, value pair`
																																							 // Assign values
		if(!strcmp(Key, "NSite")) 						Config->NSite = atoi(Value);
		if(!strcmp(Key, "NThermalize")) 			Config->NThermalize = atoi(Value);
		if(!strcmp(Key, "NEvent")) 						Config->NEvent = atoi(Value);

		if(!strcmp(Key, "HotStart")) 					Config->HotStart = atoi(Value);
		if(!strcmp(Key, "LatticeRange"))
			sscanf(Value, "%lf %lf", Config->LatticeRange, Config->LatticeRange + 1);
		if(!strcmp(Key, "ShiftMax"))					Config->ShiftMax = atof(Value);

		if(!strcmp(Key, "Step"))							Config->Step = atof(Value);
		if(!strcmp(Key, "HBar"))							Config->HBar = atof(Value);

		if(!strcmp(Key, "Potential")){
			Config->NPot = 0;

			char *Par = strtok(Value, " ");
    	while(Par != NULL){
    		Config->Potential[Config->NPot++] = atof(Par);
    	 	Par = strtok(NULL, " ");
    	}
		}

	}
}

void PrintConfiguration(Parameter *Config){
	printf("NSite : %d\n", Config->NSite);
	printf("NThermalize : %d\n", Config->NThermalize);
	printf("NEvent : %d\n", Config->NEvent);
	printf("HotStart : %d\n", Config->HotStart);
	printf("LatticeRange : [%f, %f]\n", Config->LatticeRange[0], Config->LatticeRange[1]);
	printf("ShiftMax : %lf\n", Config->ShiftMax);
	printf("Step : %lf\n", Config->Step);
	printf("HBar : %lf\n", Config->HBar);

	int n;
	printf("Potential : ");
	for(n = 0; n < Config->NPot; n++)
		printf("%f \t", Config->Potential[n]);
	printf("\n");

}


#endif