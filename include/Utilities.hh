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

//Geant4 Headers
#include "G4ThreeVector.hh"


typedef struct {
	
	int x_length;
	int y_length;
	
	G4double **array;
	
	
} VectorG4doubleStruct;

int DetermineFileLength(char *filename);

VectorG4doubleStruct *Get_VectorStruct_FromFile(char *filename, G4double dummy);

template <typename T>
void Initialize2dArray(int x_length, int y_length, T **array);

#endif

