/*
 * ReadGammaAttenuation.cxx
 * 
 * Copyright 2017 Hunter Sullivan <hunter.sullivan@mavs.uta.edu>
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

/***MUST DEFINE NUMBER OF EVENTS SIMULATED AND LIST ALL DATA SHEETS FROM DG4 IN FILENAMES***/

/*
 * HEADERS
 * 
 * */
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include <string>
using namespace std;

/*
 * PROTOYPES
 * 
 * */
void ReadFile(ifstream* );
bool PassThrough(ifstream* );

/*
 * MAIN
 * 
 * */
int main()
{
	
	string filenames[8] = {"/home/hunter/projects/DarkGeant4/config/module/GammaAttenuation/Ag/1000keV/Point625.dat",
                           "/home/hunter/projects/DarkGeant4/config/module/GammaAttenuation/Ag/1000keV/1Point250.dat",
                           "/home/hunter/projects/DarkGeant4/config/module/GammaAttenuation/Ag/1000keV/1Point875.dat",
                           "/home/hunter/projects/DarkGeant4/config/module/GammaAttenuation/Ag/1000keV/2Point5.dat",
                           "/home/hunter/projects/DarkGeant4/config/module/GammaAttenuation/Ag/500keV/Point625.dat",
                           "/home/hunter/projects/DarkGeant4/config/module/GammaAttenuation/Ag/500keV/1Point250.dat",
                           "/home/hunter/projects/DarkGeant4/config/module/GammaAttenuation/Ag/500keV/1Point875.dat",
                           "/home/hunter/projects/DarkGeant4/config/module/GammaAttenuation/Ag/500keV/2Point5.dat"};
                          
	ifstream file;
	
	for (int i = 0; i < 8; i++){
		file.open(filenames[i].c_str());
		if(file.fail()) {
		cout << "Error. Cannot find file " << filenames[i] << endl;
		exit(1);
		}
		if (i < 4){
			cout << "1000 keV----->   ";
		}
		if (i >= 4){
			cout << "400 keV----->   ";
		}
		
		ReadFile(&file);
		file.close();
	}
}

/*
 * ReadFile
 * 
 * */
void ReadFile(ifstream* currentFile)
{
	string word = "";
	int events = 0;
	int passed = 0;
	
	while (events < 10000){
	
		while (word != "Event"){   //find Event
			*currentFile >> word;
		}
		events++;
		
		while (word != "Parent"){  //find Parent
			*currentFile >> word;
		}
	
		*currentFile >> word;   //read ID
		*currentFile >> word;   //read =
		*currentFile >> word;   //read number
	
		if (word == "0"){
			if (PassThrough(currentFile)){
				passed++;
			}
		}
	}
	
	cout << "Events = " << events << "     Passed = " << passed/10000.0 << "\n";
}

/*
 * PASS THROUGH
 * 
 * */
bool PassThrough(ifstream* currentFile)
{
	string word = "";
	
	*currentFile >> word;
	*currentFile >> word;
	
	while (word != "World" && word != "OutOfWorld" && word != "*********************************************"){
		*currentFile >> word;
	}
	
	if (word == "World" || word == "OutOfWorld"){
		return true;
	}
	return false;
}
