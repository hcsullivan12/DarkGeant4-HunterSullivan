/*
 * EccentricAnomalyCalculator.hh
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


#ifndef ECCENTRICANOMALYCALCULATOR_HH
#define ECCENTRICANOMALYCALCULATOR_HH

class EccentricAnomalyCalculator {
	
	/*
     * 
     * Class member functions
     * 
     * */
	
	public:
	
		EccentricAnomalyCalculator(double e, double E);
		~EccentricAnomalyCalculator();
		
		void Calculate();
		double GetE();
		
	/*
     * 
     * Class member variables
     * 
     * */
	
	private:
		
		double deltaE;
		double e;
		double E;
		double Mdot;
		double delta;
	
};

#endif

