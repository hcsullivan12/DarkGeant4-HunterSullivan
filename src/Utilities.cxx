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

