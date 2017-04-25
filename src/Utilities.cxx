/*
 * Utilities.cxx
 * 
 * Copyright 2016 Emma Davenport <Davenport.physics@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include "Utilities.hh"

// C/C++ Headers
#include <cstdio>
#include <ctime>

string ConvertIntToString(int integer) {

	char tempstring[128] = {'\0'};
	sprintf(tempstring, "%d", integer);
	return string(tempstring);
	
}

int DetermineFileLength(string filename) {
	
	FILE *fp = fopen(filename.c_str(), "r");
	
	if (fp == NULL) {
	
		printf("File %s not found\n", filename.c_str());
		return -1;
		
	}
	
	int i = 0;
	char tempbuffer[256];
	while (fgets(tempbuffer, 256, fp) != NULL)
		i++;
		
	fclose(fp);
	return i;
	
}

int DetermineNumberOfEvents(string filename) {

	int FileLength = DetermineFileLength(filename);
	int NumberOfEvents = 0;
	
	FILE *fp = fopen(filename.c_str(), "r");
	
	char tempbuffer[256];
	for (int i = 0;i < FileLength-1;i++)
		fgets(tempbuffer, 256, fp);
	fscanf(fp,"%d:", &NumberOfEvents);
	fclose(fp);
	
	return NumberOfEvents+1;
}

double GetRandomDouble() {
	
	return ((double)rand())/((double)RAND_MAX);
	
}

struct ParticleMasses {
	
	G4String name;
	G4double mass;
	
};

static const int NumberOfMasses = 3;
ParticleMasses Masses[NumberOfMasses] = 
{{"proton"   , .9382720813},
 {"neutron"  , .9395654133},
 {"electron" , .000510998946}};
 
G4double GetParticleKineticEnergy(string particle, G4double E) {
	
	for (int i = 0;i < NumberOfMasses; i++) {
	
		if (particle == Masses[i].name)
			return E - Masses[i].mass;
			
	}
	printf("Was unable to find kinetic energy of %s\n", particle.c_str());
	return E;
}

