/*
 * HorizonCalculator.cxx
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

#include "HorizonCalculator.hh"
#include <math.h>
#include <cmath>
#include <iostream>
using namespace std;

HorizonCalculator::HorizonCalculator(double DEC, double H, double latitude){
	
	this->DEC = DEC;
	this->H = H;
	this->latitude = latitude;
	
}

HorizonCalculator::~HorizonCalculator() {
}

void HorizonCalculator::Calculate() {
	
	double sinAlt = sin(DEC*(3.14159265359/180))*sin(latitude*(3.14159265359/180)) + cos(DEC*(3.14159265359/180))*cos(latitude*(3.14159265359/180))*cos(H*(3.14159265359/180));
	//cout << "sina is: " << sinAlt << endl;
	altitude = asin(sinAlt)*(180/3.14159265359);
	
	double cosA = (sin(DEC*(3.14159265359/180)) - sin(latitude*(3.14159265359/180))*sin(altitude*(3.14159265359/180)))/(cos(latitude*(3.14159265359/180))*cos(altitude*(3.14159265359/180)));
	//cout << "cosA is: " << cosA << endl;
	azimuth = acos(cosA)*(180/3.14159265359);
	
	//cout << "sinH is: " << sin(H*(3.14159265359/180)) << endl;
	
	if (sin(H*(3.14159265359/180)) > 0) {
		azimuth = 360 - azimuth;
	}
	
}

double HorizonCalculator::GetAltitude() {
	return altitude;
}

double HorizonCalculator::GetAzimuth() {
	return azimuth;
}




