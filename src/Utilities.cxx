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

// C/C++ Headers
#include <cstdio>

#include "Utilities.hh"


int DetermineFileLength(char *filename) {
	
	FILE *fp = fopen(filename, "r");
	
	if (fp == NULL) {
	
		printf("File %s not found", filename);
		return -1;
		
	}
	
	int i = 0;
	char tempbuffer[256];
	while (fgets(tempbuffer, 256, fp) != NULL)
		i++;
		
	return i;
	
}
VectorG4doubleStruct *Get_VectorStruct_FromFile(char *filename, G4double dummy) {
	
	int FileLength = DetermineFileLength(filename);
	
	if (FileLength <= 0) {
	
		printf("File %s invalid. Unable to create VectorG4doubleStruct",
				filename);
		return NULL;
		
	}
	
	VectorG4doubleStruct *ThisStruct = new VectorG4doubleStruct;
	ThisStruct->x_length = 4;
	ThisStruct->y_length = FileLength;
	Initialize2dArray(ThisStruct->x_length,
                      ThisStruct->y_length,
                      ThisStruct->array);
	 
	for (int i = 0; i < FileLength;i++) {
	
		
		
	}
	
	return ThisStruct;
	
}

template <typename T>
void Initialize2dArray(int x_length, int y_length, T **array) {

	array = new T*[y_length];
	
	for (int x = 0;x < y_length;x++) {
	
		array[x] = new T[x_length];
		
	}
	
}
