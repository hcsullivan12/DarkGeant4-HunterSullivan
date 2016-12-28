/*
 * Read_Particle_File_Corsika.cxx
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

void readParticleFile();  //Prototypes
void printRunDate(double );
string getLowEnergyHadronModel(double );
string getHighEnergyHadronModel(double );
void printParticleData(const double [39][7]);
string getParticleName(double );

int main() {
	
	readParticleFile();
	
}

void readParticleFile() {
	
	//Open the file
	ifstream ParticleFile;
	ParticleFile.open("/home/hunter/Desktop/Corsika/corsika-75600/src/utils/boom/fort.7");
	
	//Test for Error
	if(ParticleFile.fail()) {
		cerr << "Error. Cannot find file." << endl;
		exit(1);
	}

	//Define Parameters
	double RUNH = 1.11111E+07;
	double Run_Number;
	double Run_Date;
	double Observation_Height;
	double Energy_Lower_Limit;
	double Energy_Upper_Limit;
	
	//Event Header (once per event)
	double EVTH = 3.33333E+07;
	double Event_Number;
	double Primary_Particle;
	double Primary_Energy;    //GeV
	double Starting_Altitude;     //g/cm^2
	double First_Interaction_Height;    //cm
	double Primary_px;   //GeV/c
	double Primary_py;   //GeV/c
	double Primary_pz;   //GeV/c
	double Zenith_Angle;   //radian
	double Azimuthal_Angle;   //radian
	double Hadron_KE_Cutoff;   //GeV
	double Muon_KE_Cutoff;    //GeV
	double Electron_KE_Cutoff;    //GeV
	double Photon_KE_Cutoff;    //GeV
	double xEarthMagField;   //microT
	double zEarthMagField;   //microT
	double Low_Energy_Hadron_Model;
	double High_Energy_Hadron_Model;
	
	//Particle Sub-block
	double Particle_ID;    //particle id x 1000 + hadr. generation x 10 + no. of obs. level
	double Particle_px;    //GeV/c
	double Particle_py;    //GeV/c
	double Particle_pz;    //in -z direction GeV/c
	double Particle_X;    //cm
	double Particle_Y;    //cm
	double Time_Since_First_Interaction;    //nsec
	
	//Helpful counters
	double word;
	int Number_of_Word = 1;
	
	//For Run Header
	while(Number_of_Word <= 273) {
		
		ParticleFile >> word;
		
		switch (Number_of_Word) {
			case 1: RUNH = word;
					break;
			case 2: Run_Number = word;
					break;
			case 3: Run_Date = word;
					break;
			case 6: Observation_Height = word;
					break;
			case 17: Energy_Lower_Limit = word;
					break;
			case 18: Energy_Upper_Limit = word;
					break;
			default: break;
		}
		
		Number_of_Word++;
	}
	
	cout << "RUNH is " << RUNH << endl;
	cout << "Run Number is " << Run_Number << endl;
	printRunDate(Run_Date);
	cout << "Observation Height is " << Observation_Height << " cm" << endl;
	cout << "Energy Lower Limit is " << Energy_Lower_Limit << " GeV" << endl;
	cout << "Energy Upper Limit is " << Energy_Upper_Limit << " GeV" << endl;
	
	
	//For Event Header
	Number_of_Word = 1;
	
	while(Number_of_Word <= 273) {
		
		ParticleFile >> word;
		
		switch (Number_of_Word) {
			case 1: EVTH = word;
					break;
			case 2: Event_Number = word;
					break;
			case 3: Primary_Particle = word;
					break;
			case 4: Primary_Energy = word;
					break;
			case 5: Starting_Altitude = word;
					break;
			case 7: First_Interaction_Height = word;
					break;
			case 8: Primary_px = word;
					break;
			case 9: Primary_py = word;
					break;
			case 10: Primary_pz = word;
					break;
			case 11: Zenith_Angle = word;
					break;
			case 12: Azimuthal_Angle = word;
					break;
			case 61: Hadron_KE_Cutoff = word;
					break;
			case 62: Muon_KE_Cutoff = word;
					break;
			case 63: Electron_KE_Cutoff = word;
					break;
			case 64: Photon_KE_Cutoff = word;
					break;
			case 71: xEarthMagField = word;
					break;
			case 72: zEarthMagField = word;
					break;
			case 75: Low_Energy_Hadron_Model = word;
					break;
			case 76: High_Energy_Hadron_Model = word;
					break;
			default: break;
		}
		
		Number_of_Word++;
	}
	
	cout << "EVTH is " << EVTH << endl;
	cout << "Event Number is " << Event_Number << endl;
	cout << "Primary Particle is " << getParticleName(Primary_Particle) << endl;
	cout << "Primary Energy is " << Primary_Energy << " GeV" << endl;
	cout << "Starting Altitude is " << Starting_Altitude << " cm" << endl;
	cout << "First Interaction Height is " << First_Interaction_Height << " cm" << endl;
	cout << "Primary px is " << Primary_px << " GeV/c" << endl;
	cout << "Primary py is " << Primary_py << " GeV/c" << endl;
	cout << "Primary pz is " << Primary_pz << " GeV/c" << endl;
	cout << "Zenith Angle is " << Zenith_Angle << " radians" << endl;
	cout << "Azimuthal Angle is " << Azimuthal_Angle << " radians" << endl;
	cout << "Hadron_KE Cutoff is " << Hadron_KE_Cutoff << " GeV" << endl;
	cout << "Muon KE Cutoff is " << Muon_KE_Cutoff << " GeV" << endl;
	cout << "Electron_KE Cutoff is " << Electron_KE_Cutoff << " GeV" << endl;
	cout << "Photon KE Cutoff is " << Photon_KE_Cutoff << " GeV" << endl;
	cout << "xEarthMagField is " << xEarthMagField << " microT" << endl;
	cout << "zEarthMagField is " << zEarthMagField << " microT" << endl;
	cout << "Low Energy Hadron Model is " << getLowEnergyHadronModel(Low_Energy_Hadron_Model) << endl;
	cout << "High Energy Hadron Model is " << getHighEnergyHadronModel(High_Energy_Hadron_Model) << endl;
	
	
	//Particle Sub-block
	int n;    //nth particle
	double ParticleData[39][7];   //array ---> 39 particles with 7 columns of data for each
	
	for(n = 0; n < 39; n++) {
		
		Number_of_Word = 0;
		
		while (Number_of_Word < 7) {
			
			//Get data
			
			ParticleFile >> word;
			
			//Columns
			switch (Number_of_Word) {
				case 0: Particle_ID = floor(word/1000);
						ParticleData[n][0] = floor(word/1000);
						break;
				case 1: Particle_px = word;
						ParticleData[n][1] = word;
						break;
				case 2: Particle_py = word;
						ParticleData[n][2] = word;
						break;
				case 3: Particle_pz = word;
						ParticleData[n][3] = word;
						break;
				case 4: Particle_X = word;
						ParticleData[n][4] = word;
						break;
				case 5: Particle_Y = word;
						ParticleData[n][5] = word;
						break;
				case 6: Time_Since_First_Interaction = word;
						ParticleData[n][6] = word;
						break;
				default: break;
			}
			
			Number_of_Word++;
		}
	}
	
	printParticleData(ParticleData);
	
	ParticleFile.close();
	exit(1);
}

void printRunDate(double Run_Date) {
	
	string RunDate;
	
	int year = (int)floor(Run_Date/10000) + 2000;
	int month = (int)floor((Run_Date - (year - 2000)*10000)/100);
	int day = Run_Date - (year - 2000)*10000 - month*100;
	
	cout << "The Run Date is " << month << "/" << day << "/" << year << endl;
	
}

string getLowEnergyHadronModel(double Low_Energy_Hadron_Model) {
	
	int input = (int)float(Low_Energy_Hadron_Model);
	string model;
	
	switch (input) {
		case 1: model = "GHEISHA";
				break;
		case 2: model = "UrQMD";
				break;
		case 3: model = "FLUKA";
				break;
		default: model = "Error";
				break;
	}
	
	return model;
}

string getHighEnergyHadronModel(double High_Energy_Hadron_Model) {
	
	int input = (int)float(High_Energy_Hadron_Model);
	string model;
	
	switch (input) {
		case 0: model = "HDPM";
				break;
		case 1: model = "VENUS";
				break;
		case 2: model = "SIBYLL";
				break;
		case 3: model = "QGSJET";
				break;
		case 4: model = "DPMJET";
				break;
		case 5: model = "NEXUS";
				break;
		case 6: model = "EPOS";
				break;
		default: model = "Error";
				break;
	}
	
	return model;
	
}

void printParticleData(const double ParticleData[39][7]) {
	
	string Columns[8] = {"Particle #", "ID", "Px (GeV/c)", "Py (GeV/c)", "Pz (GeV/c)", "X (cm)", "Y (cm)", "      Delta t (ns)"};
	
	cout << "\n\n";
	
	//Print Table Header
	for(int i = 0; i < 8; i++) {
		
		if (i == 7) {
			cout << setw(20) << Columns[i] << endl;
		}
		
		else cout << Columns[i] << setw(20);
		
	}
	
	cout << "\n";
	
	//Print Array Data
	for (int n = 0; n < 39; n++) {
		
		cout << "Particle " << n + 1;
		
		for (int j = 0; j < 7; j++) {
			
			if (j == 0) {
				cout << setw(20) << getParticleName(ParticleData[n][j]);
			}
			
			if (j == 6) {
				cout << setw(20) << ParticleData[n][j] << endl;
			}
			
			if (j != 0 && j != 6) {
				cout << setw(20) << ParticleData[n][j];
			}
		}
	}
}

string getParticleName(double currentParticleID) {
	
	int ID = (int)floor(currentParticleID);
	string ParticleName;
	
	switch (ID) {
		
		case 1: ParticleName = "gamma";
				break;
		case 2: ParticleName = "positron";
				break;
		case 3: ParticleName = "electron";
				break;
		case 5: ParticleName = "muon+";
				break;
		case 6: ParticleName = "muon-";
				break;
		case 8: ParticleName = "pion+";
				break;
		case 9: ParticleName = "pion-";
				break;
		case 13: ParticleName = "neutron";
				break;
		case 14: ParticleName = "proton";
				break;
		case 15: ParticleName = "antiproton";
				break;
		case 66: ParticleName = "electron neutrino";
				break;
		case 67: ParticleName = "anti electron neutrino";
				break;
		case 68: ParticleName = "muon neutrino";
				break;
		case 69: ParticleName = "anti muon neutrino";
				break;
		case 75: ParticleName = "muon+ (add. info)";
				break;
		case 76: ParticleName = "muon- (add. info)";
				break;
		case 133: ParticleName = "tauon neutrino";
				break;
		case 134: ParticleName = "anti tauon neutrino";
				break;
		default: ParticleName = "Error";
	}
	
	return ParticleName;
	
}

