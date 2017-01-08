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

/*------------------HEADERS-------------------*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include <string>
using namespace std;
/*---------------------------------------------*/

/*-----------------PROTOTYPES--------------------*/
void readParticleFile();     
void printRunDate(double );
void getNumberOfShowers(ifstream* , double );
void writeShowerAndParticleData(int , double ** , double ***);
void removeExe();

void Initialize_ParticleNamesArray();
void Initialize_ParticleMassesArray()

void FreeGlobalStaticResources();

string getParticleName(double );

double getParticleZ(ifstream* , double );
double getParticleEnergy(double , double , double , double );
/*-----------------------------------------------*/

/*-----------------GLOBAL VARIABLES------------------*/
static const double EVTH = 3.33000E+02;
static const double RUNE = 7.77000E+02;
static int Number_of_Showers;
/*---------------------------------------------------*/

int main() {
	
	Initialize_ParticleNamesArray();
	Initialize_ParticleMassesArray();
	
	cout << "\n\n";
	cout << "---------SIMULATION RUN FOR CORSIKA---------\n\n";
	
	readParticleFile();
	
	removeExe();
	FreeGlobalStaticResources();
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
	
	
	

	double word = 0.0;
	
	//READ RUN HEADER
	double Particle_Z = getParticleZ(&ParticleFile, word);
	getNumberOfShowers(&ParticleFile, word);
	
	//READ EVENT HEADERS
	    //kth shower
	    //nth particle of kth shower(up to 39 per shower)
	    
	double **ShowerData = new double*[Number_of_Showers];
	double ***ParticleData = new double**[Number_of_Showers];
	
	for (int i = 0;i < Number_of_Showers;i++)
		ShowerData[i] = new double[10];
		
	for (int i = 0; i < Number_of_Showers;i++) {
			ParticleData[i] = new double*[39];
			for (int j = 0;j < 39;j++)
				ParticleData[i][j] = new double[7];
		
	}
	                   
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
	                   
	/*      ParticleData[k][n][0]     Particle_ID;                      (particle id x 1000 + hadr. generation x 10 + no. of obs. level)
	        ParticleData[k][n][1]     Particle_px;                      (GeV/c)
	        ParticleData[k][n][2]     Particle_py;                      (GeV/c)
	        ParticleData[k][n][3]     Particle_pz;                      (in z direction GeV/c)
	        ParticleData[k][n][4]     Particle_X;                       (m)
	        ParticleData[k][n][5]     Particle_Y;                       (m)
	        ParticleData[k][n][6]     Particle_Z;                       (m) */
	
	   
	                            
	int Number_of_Word;

	for (int k = 1; k <= Number_of_Showers; k++) {
		    
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
		
		ParticleFile >> word;
		
		if (word != RUNE) {
			
			/*------------------CONTENT OF kth SHOWER PARTICLE SUB-BLOCK------------------*/
			for(int n = 1; n <= 39; n++) {
		
				ParticleData[k-1][n-1][6] = Particle_Z/100;			//CHECK THIS!!!! UNITS
				Number_of_Word = 1;
		
				//EACH PARTICLE HAS 7 COLUMNS
				while (Number_of_Word <= 7) {
				
					switch (Number_of_Word) {
						case 1: ParticleData[k-1][n-1][0] = floor(word/1000);           break;
						case 2: ParticleData[k-1][n-1][1] = word;                       break;
						case 3: ParticleData[k-1][n-1][2] = word;                       break;
						case 4: ParticleData[k-1][n-1][3] = word*-1;                    break;
						case 5: ParticleData[k-1][n-1][4] = word/100;                   break;
						case 6: ParticleData[k-1][n-1][5] = word/100;                   break;
						default:                                                        break;
					}
			
					Number_of_Word++;
					ParticleFile >> word;
				}
			}
		}
	}
	
	ParticleFile.close();
	
	writeShowerAndParticleData(Number_of_Showers, ShowerData, ParticleData);
	
	delete [] ParticleData;
	delete [] ShowerData;
}

/*
 * getParticleZ()
 * 
 *        Obtains the Z coordinate for the shower particles. This is just the observational height
 *        listed in the Run Header. Also prints out run information.
 * 
 * 
 * */

double getParticleZ(ifstream* ParticleFile, double word) {
	
	/*RUN HEADER VARIABLES*/
	double Run_Number;
	double Run_Date;
	double Observation_Height;
	double Energy_Lower_Limit;
	double Energy_Upper_Limit;
	
	/*CONTENT OF RUN HEADER*/
	int Number_of_Word = 1;
	
	while(Number_of_Word <= 92) {
		
		*ParticleFile >> word;
		
		switch (Number_of_Word) {
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
	cout << "Run Number is " << Run_Number << endl;
	printRunDate(Run_Date);
	cout << "Observation Height is " << Observation_Height/100 << " m above sea level" << endl;
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

void getNumberOfShowers(ifstream* ParticleFile, double word) {
	
	*ParticleFile >> word;   //93rd word in block
	
	Number_of_Showers = word;
	
	cout << "Number of showers is " << Number_of_Showers << endl;
	cout << "\n";
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

void writeShowerAndParticleData(int Number_of_Showers, double **ShowerData, double ***ParticleData) {
	
	ofstream OutputFile;
	OutputFile.open ("/home/hunter/projects/DarkGeant4/config/Particle_Data.txt");
	
	//string ShowerRows[9] = {"Primary ID:", "Primary Energy(GeV):", "Starting Altitude(cm):", "First Interaction Height(cm):", "Primary Px(GeV/c):", "Primary Py(GeV/c):", "Primary Pz(GeV/c):", "Zenith Angle(rad):", "Azimuthal Angle(rad):"};
	//string ParticleColumns[8] = {"ID", "E/c", "Px (GeV/c)", "Py (GeV/c)", "Pz (GeV/c)", "X (cm)", "Y (cm)", "Z (cm)"};    
	
	int NumberOfParticles = 0;
	
	double muMinusEnergies = 0.0;
	int muMinus = 0;
	
	double muPlusEnergies = 0.0;
	int muPlus = 0;
	
	double gammaEnergies = 0.0;
	int gammas = 0;
	
	double eMinusEnergies = 0.0;
	int eMinus = 0;
	
	double ePlusEnergies = 0.0;
	int ePlus = 0;
	
	double neutronEnergies = 0.0;
	int neutrons = 0;
	
	double protonEnergies = 0.0;
	int protons = 0;
	
	int unknowns = 0;
	
	if (OutputFile.is_open()) {
	
		for (int k = 1; k <= Number_of_Showers; k++) {
		
			/*PRINT DATA IN PARTICLE ARRAY*/
			for (int n = 1; n <= 39; n++) {
				
				if (getParticleName(ParticleData[k-1][n-1][0]) != "Unknown") {
				
					if (ParticleData[k-1][n-1][0] != 0) {
					
						NumberOfParticles++;
						
							for (int j = 0; j < 7; j++) {
			
								if (j == 0) {
									OutputFile << 0 << ":";
									OutputFile << setw(10) << getParticleName(ParticleData[k-1][n-1][j]);
									if (ParticleData[k-1][n-1][j] == 6 || ParticleData[k-1][n-1][j] == 76){
										muMinusEnergies = muMinusEnergies + getParticleEnergy(ParticleData[k-1][n-1][0], ParticleData[k-1][n-1][1], ParticleData[k-1][n-1][2], ParticleData[k-1][n-1][3]);
										muMinus++;
									}
									if (ParticleData[k-1][n-1][j] == 5 || ParticleData[k-1][n-1][j] == 75){
										muPlusEnergies = muPlusEnergies + getParticleEnergy(ParticleData[k-1][n-1][0], ParticleData[k-1][n-1][1], ParticleData[k-1][n-1][2], ParticleData[k-1][n-1][3]);
										muPlus++;
									}
									if (ParticleData[k-1][n-1][j] == 1){
										gammaEnergies = gammaEnergies + getParticleEnergy(ParticleData[k-1][n-1][0], ParticleData[k-1][n-1][1], ParticleData[k-1][n-1][2], ParticleData[k-1][n-1][3]);
										gammas++;
									}
									if (ParticleData[k-1][n-1][j] == 3){
										eMinusEnergies = eMinusEnergies + getParticleEnergy(ParticleData[k-1][n-1][0], ParticleData[k-1][n-1][1], ParticleData[k-1][n-1][2], ParticleData[k-1][n-1][3]);
										eMinus++;
									}
									if (ParticleData[k-1][n-1][j] == 2){
										ePlusEnergies = ePlusEnergies + getParticleEnergy(ParticleData[k-1][n-1][0], ParticleData[k-1][n-1][1], ParticleData[k-1][n-1][2], ParticleData[k-1][n-1][3]);
										ePlus++;
									}
									if (ParticleData[k-1][n-1][j] == 13){
										neutronEnergies = neutronEnergies + getParticleEnergy(ParticleData[k-1][n-1][0], ParticleData[k-1][n-1][1], ParticleData[k-1][n-1][2], ParticleData[k-1][n-1][3]);
										neutrons++;
									}
									if (ParticleData[k-1][n-1][j] == 14){
										protonEnergies = protonEnergies + getParticleEnergy(ParticleData[k-1][n-1][0], ParticleData[k-1][n-1][1], ParticleData[k-1][n-1][2], ParticleData[k-1][n-1][3]);
										protons++;
									}									
									if (getParticleName(ParticleData[k-1][n-1][j]) == "Unknown"){
										unknowns++;
									}
									OutputFile << setw(15) << right << getParticleEnergy(ParticleData[k-1][n-1][0], ParticleData[k-1][n-1][1], ParticleData[k-1][n-1][2], ParticleData[k-1][n-1][3]);
								}
							
								if (j == 6) {
									OutputFile << setw(15) << right << ParticleData[k-1][n-1][j] << endl;
								}
					
								if (j != 0 && j != 6) {
									OutputFile << setw(15) << right << ParticleData[k-1][n-1][j];
								}
							}
						}
					}
				}
			}
	
			OutputFile.close();
	}
	
	else cout << "Unable to open file.";
	
	cout << "The number of particles detected is " << NumberOfParticles << "\n\n";
	
	cout << "The average muon- energy is " << muMinusEnergies/muMinus << " GeV\n";
	cout << "The number of muon- detected is " << muMinus << "\n\n";
	
	cout << "The average muon+ energy is " << muPlusEnergies/muPlus << " GeV\n";
	cout << "The number of muon+ detected is " << muPlus << "\n\n";
	
	cout << "The average gamma energy is " << gammaEnergies/gammas << " GeV\n";
	cout << "The number of gammas detected is " << gammas << "\n\n";
	
	cout << "The average e- energy is " << eMinusEnergies/eMinus << " GeV\n";
	cout << "The number of e- detected is " << eMinus << "\n\n";
	
	cout << "The average e+ energy is " << ePlusEnergies/ePlus << " GeV\n";
	cout << "The number of e+ detected is " << ePlus << "\n\n";
	
	cout << "The average neutron energy is " << neutronEnergies/neutrons << " GeV\n";
	cout << "The number of neutrons detected is " << neutrons << "\n\n";
	
	cout << "The average proton energy is " << protonEnergies/protons << " GeV\n";
	cout << "The number of protons detected is " << protons << "\n\n";
	
	cout << "The number of unknowns is " << unknowns << "\n";
}

static double *ParticleMasses;
void Initialize_ParticleMassesArray() {
	
	ParticleMasses = new double[200];
	ParticleMasses[2] = 0.5109989461;
	ParticleMasses[3] = 0.5109989461;
	ParticleMasses[5] = 105.6583745;
	ParticleMasses[6] = 105.6583745;
	ParticleMasses[8] = 139.57018;
	ParticleMasses[9] = 139.57018;
	ParticleMasses[13] = 939.5654133;
	ParticleMasses[14] = 938.2720813;
	ParticleMasses[15] = 938.2720813;
	ParticleMasses[75] = 105.6583745;
	ParticleMasses[76] = 105.6583745;
	
}

/*
 * getParticleEnergy()
 * 
 *        Obtains and returns E/c quantity for print out.
 * 
 * 
 * */

double getParticleEnergy(double ID, double Px, double Py, double Pz) {

	double P2 = Px*Px + Py*Py + Pz*Pz;
	double mass = ParticleMasses[(int)ID]/1000;

	return sqrt(P2 + mass*mass);
}


static string *ParticleName;

void Initialize_ParticleNamesArray() {
	
	ParticleName = new string[200];
	ParticleName[1] = "gamma";
	ParticleName[2] = "e+";
	ParticleName[3] = "e-";
	ParticleName[5] = "mu+";
	ParticleName[6] = "mu-";
	ParticleName[8] = "pi+";
	ParticleName[9] = "pi-";
	ParticleName[13] = "neutron";
	ParticleName[14] = "proton";
	ParticleName[15] = "antiproton";
	ParticleName[66] = "electron neutrino";
	ParticleName[67] = "anti electron neutrino";
	ParticleName[68] = "muon neutrino";
	ParticleName[69] = "anti muon neutrino";
	ParticleName[75] = "(add. info) mu+";
	ParticleName[133] = "tauon neutrino";
	ParticleName[134] = "anti tauon neutrino";
	
}

/*
 * getParticleName()
 * 
 *         Obtains the name of each particle. I've only provided a few.
 * 
 * 
 * */

string getParticleName(double currentParticleID) {
	
	return ParticleName[(int)floor(currentParticleID)];
	
}

void removeExe() {
	
	remove("/home/hunter/projects/DarkGeant4/scripts/corsika/ReadCorsikaParticles");
	
}

void FreeGlobalStaticResources() {
	
	delete [] ParticleName;
	delete [] ParticleMasses;
	
}
