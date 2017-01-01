/*
 * ReadCorsikaParticles.cxx
 * 
 * Copyright 2016 Hunter Sullivan <hunter.sullivan@mavs.uta.edu>
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

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include <string>
using namespace std;

void readParticleFile();     //PROTOTYPES
void printRunDate(double );
void writeShowerAndParticleData(int , const double [][10] , const double [][39][7]);
string getParticleName(double );
double getParticleZ(ifstream& , double );
int getNumberOfShowers(ifstream& , double );
double getParticleEnergy(double , double , double , double );


int main() {
	
	cout << "\n\n";
	cout << "---------SIMULATION RUN FOR CORSIKA---------\n\n";
	
	readParticleFile();
	
	
	
}

/*
 * readParticleFile()
 * 
 *        Reads from particle output file that Corsika produces. Event headers start with 3.33000E+02.
 *        From there, data is extracted into Shower and (secondary) Particle arrays.
 * 
 * 
 * */

void readParticleFile() {
	
	//OPEN THE FILE
	ifstream ParticleFile;
	ParticleFile.open("/home/hunter/projects/Corsika/run/build/fort.7");
	
	//TEST FOR ERROR
	if(ParticleFile.fail()) {
		cerr << "Error. Cannot find file." << endl;
		exit(1);
	}
	
	double EVTH = 3.33000E+02;
	

	double word = 0.0;
	
	//READ RUN HEADER
	double Particle_Z = getParticleZ(ParticleFile, word);
	int Number_of_Showers = getNumberOfShowers(ParticleFile, word);
	
	//READ EVENT HEADERS
	    //kth shower
	    //nth particle of kth shower(up to 39 per shower)
	    
	double ShowerData[Number_of_Showers][10];                           
		/*  ShowerData[k][0]          Event Header = 3.33000E+02;       (particle id x 1000 + hadr. generation x 10 + no. of obs. level)
	        ShowerData[k][1]          Primary ID;                      
	        ShowerData[k}[2]          Primary Energy;                   (GeV)
	        ShowerData[k][3]          Primary Starting Altitude;        (cm)           CHECK UNITS AT SOME POINT
	        ShowerData[k][4]          First Interaction Height;         (cm)
	        ShowerData[k][5]          Primary_px;                       (GeV/c)
	        ShowerData[k][6]          Primary_py;                       (GeV/c)
	        ShowerData[k][7]          Primary_pz;                       (GeV/c) 
	        ShowerData[k][8]          Zenith Angle;                     (radians)
	        ShowerData[k][9]          Azimuthal Angle;                  (radians) */
	
	double ParticleData[Number_of_Showers][39][7];                      
	/*      ParticleData[k][n][0]     Particle_ID;                      (particle id x 1000 + hadr. generation x 10 + no. of obs. level)
	        ParticleData[k][n][1]     Particle_px;                      (GeV/c)
	        ParticleData[k][n][2]     Particle_py;                      (GeV/c)
	        ParticleData[k][n][3]     Particle_pz;                      (in -z direction GeV/c)
	        ParticleData[k][n][4]     Particle_X;                       (cm)
	        ParticleData[k][n][5]     Particle_Y;                       (cm)
	        ParticleData[k][n][6]     Particle_Z;                       (cm) */
	
	   
	                            
	int Number_of_Word;
	int k;                                                              //kth shower
	int n;                                                              //nth particle, Prints up to 39 particles for each shower
	
	for (k = 1; k <= Number_of_Showers; k++) {
		    
		    while (word != EVTH) {                                      //Find shower headers
				ParticleFile >> word;
			}
		
		Number_of_Word = 2;
		ShowerData[k-1][0] = word;
		
		
		/*------------------CONTENT OF kth SHOWER HEADER------------------*/
		while(Number_of_Word <= 273) {
		
			ParticleFile >> word;
		
			switch (Number_of_Word) {
				case 3: ShowerData[k-1][1] = word;       break;
				case 4: ShowerData[k-1][2] = word;       break;
				case 5: ShowerData[k-1][3] = word;       break;
				case 7: ShowerData[k-1][4] = word;       break;
				case 8: ShowerData[k-1][5] = word;       break;
				case 9: ShowerData[k-1][6] = word;       break;
				case 10: ShowerData[k-1][7] = word;      break;
				case 11: ShowerData[k-1][8] = word;      break;
				case 12: ShowerData[k-1][9] = word;      break;
				default:                                 break;
			}
		
			Number_of_Word++;
		}

		/*------------------CONTENT OF kth SHOWER PARTICLE SUB-BLOCK------------------*/
		for(n = 1; n <= 39; n++) {
		
			ParticleData[k-1][n-1][6] = Particle_Z;
			Number_of_Word = 1;
		
			//EACH PARTICLE HAS 7 COLUMNS
			while (Number_of_Word <= 7) {
			
				//GET DATA
				ParticleFile >> word;
				
				switch (Number_of_Word) {
					case 1: ParticleData[k-1][n-1][0] = floor(word/1000);           break;
					case 2: ParticleData[k-1][n-1][1] = word;                       break;
					case 3: ParticleData[k-1][n-1][2] = word;                       break;
					case 4: ParticleData[k-1][n-1][3] = word;                       break;
					case 5: ParticleData[k-1][n-1][4] = word;                       break;
					case 6: ParticleData[k-1][n-1][5] = word;                       break;
					default:                                                        break;
				}
			
				Number_of_Word++;
			}
		}
	}
	
	ParticleFile.close();
	
	writeShowerAndParticleData(Number_of_Showers, ShowerData, ParticleData);
	
}

/*
 * getParticleZ()
 * 
 *        Obtains the Z coordinate for the shower particles. This is just the observational height
 *        listed in the Run Header. Also prints out run information.
 * 
 * 
 * */

double getParticleZ(ifstream& ParticleFile, double word) {
	
	/*RUN HEADER VARIABLES*/
	double RUNH = 1.11111E+07;
	double Run_Number;
	double Run_Date;
	double Observation_Height;
	double Energy_Lower_Limit;
	double Energy_Upper_Limit;
	
	/*CONTENT OF RUN HEADER*/
	int Number_of_Word = 1;
	
	while(Number_of_Word <= 92) {
		
		ParticleFile >> word;
		
		switch (Number_of_Word) {
			case 1: RUNH =                       word; break;
			case 2: Run_Number =                 word; break;  
			case 3: Run_Date =                   word; break;
			case 6: Observation_Height =         word; break;
			case 17: Energy_Lower_Limit =        word; break;
			case 18: Energy_Upper_Limit =        word; break;
			default:                                   break;
		}
		
		Number_of_Word++;
	}
	
	cout << "----RUN INFO----" << endl;
	cout << "RUNH is " << RUNH << endl;
	cout << "Run Number is " << Run_Number << endl;
	printRunDate(Run_Date);
	cout << "Observation Height is " << Observation_Height << " cm" << endl;
	cout << "Energy Lower Limit is " << Energy_Lower_Limit << " GeV" << endl;
	cout << "Energy Upper Limit is " << Energy_Upper_Limit << " GeV" << endl;	
	
	return Observation_Height;
}

/*
 * getNumberOfShowers()
 * 
 *        Obtains the number of showers simulated in Corsika. This is in the Run Header.
 * 
 * */

int getNumberOfShowers(ifstream& ParticleFile, double word) {
	
	int Number_of_Showers;
	
	ParticleFile >> word;   //93rd word in block
	
	Number_of_Showers = word;
	
	cout << "Number of showers is " << Number_of_Showers << endl;
	cout << "\n";
	
	return Number_of_Showers;
}

/*
 * printRunDate()
 * 
 * 
 * */

void printRunDate(double Run_Date) {
	
	string RunDate;
	
	int year = (int)floor(Run_Date/10000) + 2000;
	int month = (int)floor((Run_Date - (year - 2000)*10000)/100);
	int day = Run_Date - (year - 2000)*10000 - month*100;
	
	cout << "The Run Date is " << month << "/" << day << "/" << year << endl;
	
}

/* writeShowerAndParticleData()
 * 
 *        Writes the particle data to a file Particle_Data.txt in a certain format given
 *        in Particles.lua.
 * 
 *        The E/c quantity is not given in particle data file, so it must be calculated from given quantities. 
 * 
 * 
 * */

void writeShowerAndParticleData(int Number_of_Showers, const double ShowerData [][10], const double ParticleData [][39][7]) {
	
	ofstream OutputFile;
	OutputFile.open ("/home/hunter/projects/Corsika/run/build/Particle_Data.txt");
	
	//string ShowerRows[9] = {"Primary ID:", "Primary Energy(GeV):", "Starting Altitude(cm):", "First Interaction Height(cm):", "Primary Px(GeV/c):", "Primary Py(GeV/c):", "Primary Pz(GeV/c):", "Zenith Angle(rad):", "Azimuthal Angle(rad):"};
	//string ParticleColumns[8] = {"ID", "E/c", "Px (GeV/c)", "Py (GeV/c)", "Pz (GeV/c)", "X (cm)", "Y (cm)", "Z (cm)"};      
	
	if (OutputFile.is_open()) {
	
		for (int k = 1; k <= Number_of_Showers; k++) {
		
			/*PRINT DATA IN PARTICLE ARRAY*/
			for (int n = 1; n <= 39; n++) {
		
				//OutputFile << "Particle " << setw(2) << n;
		
				for (int j = 0; j < 7; j++) {
			
					if (j == 0) {
						OutputFile << getParticleName(ParticleData[k-1][n-1][j]) << ", ";
						OutputFile << getParticleEnergy(ParticleData[k-1][n-1][0], ParticleData[k-1][n-1][1], ParticleData[k-1][n-1][2], ParticleData[k-1][n-1][3]) << ", ";
					}
					
					if (j == 6) {
						OutputFile << ParticleData[k-1][n-1][j] << endl;
					}
					
					if (j != 0 && j != 6) {
						OutputFile << ParticleData[k-1][n-1][j] << ", ";
					}
				}
			}
		}
	
		OutputFile.close();
	}
	
	else cout << "Unable to open file.";

}

/*
 * getParticleEnergy()
 * 
 *        Obtains and returns E/c quantity for print out.
 * 
 * 
 * */

double getParticleEnergy(double ID, double Px, double Py, double Pz) {
	
	double energy_c;
	
	double P2 = Px*Px + Py*Py + Pz*Pz;
	double mass;
	double ParticleMasses[200];
	
	for (int i = 1; i <= 200; i++){
		
		switch (i) {
		//in MeV/c^2
		case 1: ParticleMasses[i] = 0;                          break;
		case 2: ParticleMasses[i] = 0.5109989461;               break;
		case 3: ParticleMasses[i] = 0.5109989461;               break;
		case 5: ParticleMasses[i] = 105.6583745;                break;
		case 6: ParticleMasses[i] = 105.6583745;                break;
		case 8: ParticleMasses[i] = 139.57018;                  break;
		case 9: ParticleMasses[i] = 139.57018;                  break;
		case 13: ParticleMasses[i] = 939.5654133;               break;
		case 14: ParticleMasses[i] = 938.2720813;               break;
		case 15: ParticleMasses[i] = 938.2720813;               break;
		case 66: ParticleMasses[i] = 0;                         break;
		case 67: ParticleMasses[i] = 0;                         break;
		case 68: ParticleMasses[i] = 0;                         break;
		case 69: ParticleMasses[i] = 0;                         break;
		case 75: ParticleMasses[i] = 0;                         break;
		case 76: ParticleMasses[i] = 0;                         break;
		case 133: ParticleMasses[i] = 0;                        break;
		case 134: ParticleMasses[i] = 0;                        break;
		}	
		
		
	}
	
	for (int i = 1; i <= 200; i++ ) {
		
		if (ID == i) {
			mass = ParticleMasses[i];
		}
	}
	
	
	energy_c = sqrt(P2 + mass*mass);
	return energy_c;
}

/*
 * getParticleName()
 * 
 *         Obtains the name of each particle. I've only provided a few.
 * 
 * 
 * */

string getParticleName(double currentParticleID) {
	
	int ID = (int)floor(currentParticleID);
	string ParticleName;
	
	switch (ID) {
		
		case 1: ParticleName = "gamma";                          break;
		case 2: ParticleName = "positron";                       break;
		case 3: ParticleName = "electron";                       break;
		case 5: ParticleName = "muon+";                          break;
		case 6: ParticleName = "muon-";                          break;
		case 8: ParticleName = "pion+";                          break;
		case 9: ParticleName = "pion-";                          break;
		case 13: ParticleName = "neutron";                       break;
		case 14: ParticleName = "proton";                        break;
		case 15: ParticleName = "antiproton";                    break;
		case 66: ParticleName = "electron neutrino";             break;
		case 67: ParticleName = "anti electron neutrino";        break;
		case 68: ParticleName = "muon neutrino";                 break;
		case 69: ParticleName = "anti muon neutrino";            break;
		case 75: ParticleName = "(add. info) muon+";             break;
		case 76: ParticleName = "(add. info) muon-";             break;
		case 133: ParticleName = "tauon neutrino";               break;
		case 134: ParticleName = "anti tauon neutrino";          break;
		default: ParticleName = "Unknown";                       break;
		
	}
	
	return ParticleName;
	
}

