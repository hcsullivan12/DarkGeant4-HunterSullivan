/*
 * JulianDayCalculator.cxx
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

#include "JulianDayCalculator.hh"
#include <math.h>
#include <cmath>

JulianDayCalculator::JulianDayCalculator(int y, int m, int d){
	
	this->y = y;
	this->m = m;
	this->d = d;
	
}

JulianDayCalculator::~JulianDayCalculator() {
}

void JulianDayCalculator::Calculate() {
	
	if (m == 1 || m == 2){
		y = y - 1;
		m = m + 12;
	}
	
	int A = y/100;
	int B = 2 - A + A/4;
	int C = trunc(365.25*y);
	int D = trunc(30.6001*(m + 1));
	JD = B + C + D + d + 1720994.5;
}

double JulianDayCalculator::GetJD() {
	return JD;
}



