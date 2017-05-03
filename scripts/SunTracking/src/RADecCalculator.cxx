/*
 * RADecCalculator.cxx
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

#include "RADecCalculator.hh"
#include <math.h>
#include <cmath>

RADecCalculator::RADecCalculator(double lambda, double T){
	
	this->lambda = lambda;
	this->T = T;
	this->RA = RA;
	this->DEC = DEC;
	
}

RADecCalculator::~RADecCalculator() {
}

void RADecCalculator::Calculate() {
	
	lambda = lambda*(3.14159265359/180);
	epsilon = (23.439292 - (46.815*T - 0.0006*T*T +0.00181*T*T*T)/3600)*(3.14159265359/180);
	double y = sin(lambda)*cos(epsilon);
	double x = cos(lambda);
	
	RA = atan(abs(y/x))*(180/3.14159265359);
	DEC = asin(sin(epsilon)*sin(lambda))*(180/3.14159265359);
	
	if(y > 0 && x < 0) {
		RA = 180 - RA;
	}
	if(y < 0 && x < 0) {
		RA = RA + 180;
	}
	if(y < 0 && x > 0) {
		RA = 360 - RA;
	}
	
	RA = RA/15;
	double hour = trunc(RA);
	double minute = trunc((RA - hour)*60);
	double seconds = trunc((((RA - hour)*60) - minute)*60);
	
	
	//cout << "RA is " + ConvertToString(hour) + "h " + ConvertToString(minute) + "m " + ConvertToString(seconds) + "s \n";
	
	
	//cout << "RA is: " << RA << " degrees" << endl;
	//cout << "Dec is: " << DEC << " degrees\n\n";
}

string RADecCalculator::ConvertToString(double value) {
	
	stringstream s;
	s << value;
	return s.str();
	
}

double RADecCalculator::GetRA() {
	return RA;
}

double RADecCalculator::GetDEC() {
	return DEC;
}

