/*
 * EccentricAnomalyCalculator.cxx
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

#include "EccentricAnomalyCalculator.hh"
#include <math.h>
#include <cmath>
using namespace std;

EccentricAnomalyCalculator::EccentricAnomalyCalculator(double e, double E) {
	
	this->e = e;
	this->E = E;
	
}

EccentricAnomalyCalculator::~EccentricAnomalyCalculator() {
}

void EccentricAnomalyCalculator::Calculate() {
	
	Mdot = E;
	delta = E - e*sin(E) - Mdot;
	
	while (abs(delta) > 0.00001) {
		deltaE = delta/(1 - e*cos(E));
		E = E - deltaE;
		delta = E - e*sin(E) - Mdot;
	}
	
}

double EccentricAnomalyCalculator::GetE() {
	return E;
}

