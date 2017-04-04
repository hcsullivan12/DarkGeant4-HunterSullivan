/*
 * Utilities.hh
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


#ifndef UTILITIES_H
#define UTILITIES_H

// C/C++ Headers
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>


//Geant4 Headers
#include "G4ThreeVector.hh"

using std::string;
using std::printf;
using std::fscanf;

template <typename T>
struct FourVectorStruct {
	
	int x_length;
	int y_length;
	
	T **array;	
	
};

struct FourVector {
	
	G4String ParticleName;
	G4double P_x, P_y, P_z;
	G4double X, Y, Z;
	G4double E;
	G4double T;
	
};

int DetermineFileLength(string filename);
int DetermineNumberOfEvents(string filename);
string ConvertIntToString(int integer);
G4double GetParticleKineticEnergy(string particle, G4double E);

// Uniform from 0.0 to 1.0
double GetRandomDouble();

template <typename T>
void Initialize2dArray(int x_length, int y_length, T ***array) {
	
	*array = new T*[y_length];
	
	for (int y = 0;y < y_length;y++) {
	
		(*array)[y] = new T[x_length];
		
	}

}

template <typename T>
FourVectorStruct<T> *Get_VectorStruct_FromFile(string filename) {

	int FileLength = DetermineFileLength(filename);
	
	if (FileLength <= 0) {
	
		printf("File %s invalid. Unable to create FourVectorStruct\n",
				filename.c_str());
		return NULL;
		
	}
	
	FourVectorStruct<T> *ThisStruct = new FourVectorStruct<T>;
	ThisStruct->x_length = 4;
	ThisStruct->y_length = FileLength;
	Initialize2dArray(ThisStruct->x_length,
                      ThisStruct->y_length,
                      &ThisStruct->array);
	
	FILE *fp = fopen(filename.c_str(), "r");
	
	if (fp == NULL) {
	
		printf("File %s not open for some reason", filename.c_str());
		return NULL;
		
	}
	
	for (int i = 0; i < FileLength;i++) {
	
		fscanf(fp, "%lf\t%lf\t%lf\t%lf\n", &ThisStruct->array[i][0],
                                           &ThisStruct->array[i][1],
                                           &ThisStruct->array[i][2],
                                           &ThisStruct->array[i][3]);
		
	}
	fclose(fp);
	
	return ThisStruct;
	
}

#endif

