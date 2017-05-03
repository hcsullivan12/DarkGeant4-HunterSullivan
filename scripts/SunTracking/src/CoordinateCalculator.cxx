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

CoordinateCalculator::CoordinateCalculator(double Altitude, double Azimuth) {
	
	this->Altitude = Altitude;
	this->Azimuth = Azimuth;
	
}

CoordinateCalculator::~CoordinateCalculator(){
}

void CoordinateCalculator::Calculate() {
	
	theta = (3.14159265359/2) - altitude;
	phi = (3.14159265359/2) - azimuth;   ///y axis points North, x axis points East
	
	dir_x = -cos(Altitude)*sin(Azimuth);
	dir_y = -cos(Altitude)*cos(Azimuth);
	dir_z = -sin(Altitude);
	
}
