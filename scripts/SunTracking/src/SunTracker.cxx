/*
 * SunTracker.cxx
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

//C++ Headers
#include <iostream>
#include <ctime>
#include <math.h>
#include <cmath>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>  
#include <fstream>
#include <cstdio>

//User Headers
#include "EccentricAnomalyCalculator.hh"
#include "HorizonCalculator.hh"
#include "JulianDayCalculator.hh"
#include "RADecCalculator.hh"
#include "CoordinateCalculator.hh"
#include "SunTracker.hh"

using namespace std;

SunTracker::SunTracker(){
}

SunTracker::~SunTracker(){
}

/* 
 * Track() 
 * 
 *        Starts the tracking process by taking user input
 * 
 * */


void SunTracker::Track(){
	
	
	///USER INPUT
	
	cout << "\n**************************************************\n";
	cout << "             WELCOME TO SUNTRACKER\n";
	cout << "**************************************************\n";
	
	cout << "\nNumber of days to track the sun:  ";
	int NumberOfDays;
	cin >> NumberOfDays;
	
	if (NumberOfDays <= 0) {
		cout << "\nError. Number of days should be greater than 0. Aborting.\n";
		exit(1);
	} 
	
	cout << "\nStart date for sun tracking\n";
	
	cout << "Enter YEAR: ";
	cin >> year;
	
	cout << "Enter MONTH (1-JAN, 2-FEB, etc.): ";
	cin >> month;
	if (month > 12) {
		cout << "\nError. Invalid month. Aborting.\n";
		exit(1);
	}
	
	cout << "Enter DAY: ";
	cin >> day;
	if (day > 31) {
		cout << "\nError. Invalid day. Aborting.\n";
		exit(1);
	}
	
	cout << "\nEnter the observation latitude:  ";
	cin >> latitude;
	if (latitude > 90 || latitude <= -90) {
		cout << "\nError. Invalid latitude. Aborting.\n";
		exit(1);
	}///degrees
	
	cout << "\n**************************************************\n";
	if (NumberOfDays == 1){
		cout << "\nCalling Tracker for " << NumberOfDays << " day starting at " << year << "-" << month << "-" << day << " for " << latitude << " degrees latitude\n";
	}
	else {
		cout << "\nCalling Tracker for " << NumberOfDays << " days starting at " << year << "-" << month << "-" << day << " for " << latitude << " degrees latitude\n";
	}
	
	cout << "Printing to File.\n\n";
	
	
	///CALCULATIONS
	 
	///Julian Date for Start Date
	JulianDayCalculator JDCalc(year, month, day); 
	JDCalc.Calculate();
	JD = JDCalc.GetJD();
	//cout << "Julian Date is: " << JD << endl;
	
	int CurrentDay = 1;
	FILE* File;
	File = fopen("SunTracking.dat", "w");
	if (File == NULL) {
		printf("Was not able to open SunTracking.dat\n");
		exit(1);
	}
	
	while (CurrentDay <= NumberOfDays) {
		
		Calculate();
		PrintTrack(CurrentDay, File);
		
		CurrentDay = CurrentDay + 1;
		JD = JD + 1;
	} 
	fclose(File);
}

/* 
 * CheckRange() 
 * 
 *        
 * 
 * */


void SunTracker::CheckRange(double *value) {
	
	while (*value < 0) {
		*value = *value + 360;
	}
	
	while (*value > 360) {
		*value = *value - 360;
	}
}

/* 
 * Calculate() 
 * 
 *        Processes the necessary calculations for tracking
 * 
 * */

void SunTracker::Calculate() {
	
	
	///Eccentric Anomaly
	T = (JD - 2415020.0)/36525;
	epsilon = 279.6966778 + 36000.76892*T + 0.0003025*T*T;
	omega_bar = 281.2208444 + 1.719175*T + 0.000452778*T*T;
	e = 0.01675104 - 0.0000418*T - 0.000000126*T*T;
	CheckRange(&epsilon);
	CheckRange(&omega_bar);
	CheckRange(&e);
	Mdot = epsilon - omega_bar;
	CheckRange(&Mdot);
	Mdot = Mdot*(3.14159265359/180);
	EccentricAnomalyCalculator EACalc(e, Mdot);
	EACalc.Calculate();
	E = EACalc.GetE(); ///in radians
	
	///Conversion to Right Ascension and Declination
	tanv = sqrt((1 + e)/(1 - e))*tan(E/2);
	v = atan(tanv)*2*(180/3.14159265359);
	if (v < 0){
		v = v + 360; ///degrees
	}
			lambda = v + omega_bar;
	if (lambda > 360) {
		lambda = lambda - 360; ///degrees
	}
	
	RADecCalculator RADecCalc(lambda, T);
	RADecCalc.Calculate();
	RA = RADecCalc.GetRA(); ///Decimal hours
	DEC = RADecCalc.GetDEC(); ///degrees
	
}

/* 
 * PrintTrack() 
 * 
 *       Prints to SunTracking.dat   
 * 
 * */
 
void SunTracker::PrintTrack(int CurrentDay, FILE* File) {
	
	///Print out Altitudes and Azimuths for Sun at given latitude
	if (CurrentDay == 1) {
		fprintf(File, "Altitude (degrees)\tAzimuth (degrees E of N)\n");
	}
	
	double h = 0;         ///Doesn't necessarily start at midnight
	H = 0;
	
	while (h <= 24) {
		H = h - RA;
		if (RA < 0) {
			H = H + 24;
		}
		H = H*15; ///degrees
		
		HorizonCalculator HorCalc(DEC, H, latitude);
		HorCalc.Calculate();
		
		CoordinateCalculator CoordCalc(HorCalc.GetAltitude(), HorCalc.GetAzimuth());
		CoordCalc.Calculate();
		
		fprintf(File, "%7.2f \t\t %7.2f\n", HorCalc.GetAltitude(), HorCalc.GetAzimuth());
		
		h = h + 0.5;
	}
}
