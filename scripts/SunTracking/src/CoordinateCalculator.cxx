/*
 * CoordinateCalculator.cxx
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


#include "CoordinateCalculator.hh"
#include <math.h>
#include <cmath>

CoordinateCalculator::CoordinateCalculator(double Altitude, double Azimuth, double beta) {
	
	this->Altitude = Altitude;
	this->Azimuth = Azimuth;
	this->beta = beta;
	
}

CoordinateCalculator::~CoordinateCalculator(){
}

/* 
 * Calculate() 
 * 
 *       Translates the altitude and azimuth angles to cartestian coordinates and rotates to detector's coordinates
 *       Coordinate system: 
 *                 z-axis --> Along longitudinal axis of detector
 *                 y-axis --> Towards zenith
 * 
 * */

void CoordinateCalculator::Calculate() {
	///Initial: y axis points North, x axis points East
	theta = 90 - Altitude;
	phi = 90 - Azimuth;   
	double Xnot = -sin(theta*(3.14159265359/180))*cos(phi*(3.14159265359/180)); 
	double Ynot = -sin(theta*(3.14159265359/180))*sin(phi*(3.14159265359/180));
	double Znot = -cos(theta*(3.14159265359/180));
	
	///Rotate: x->North, z->E, y->zenith 
	double Xprime = Ynot;
	double Yprime = Znot;
	double Zprime = Xnot;
	
	///Rotate: z->logitudinal axis of detector
	Z = Zprime*cos((90-beta)*(3.14159265359/180)) + Xprime*sin((90-beta)*(3.14159265359/180));
	X = -Zprime*sin((90-beta)*(3.14159265359/180)) + Xprime*cos((90-beta)*(3.14159265359/180));
	Y = Yprime;
	
}

/* 
 * GetjComponent() 
 * 
 * 
 * */

double CoordinateCalculator::GetXComponent() {
	return X;
}

double CoordinateCalculator::GetYComponent() {
	return Y;
}

double CoordinateCalculator::GetZComponent() {
	return Z;
}
