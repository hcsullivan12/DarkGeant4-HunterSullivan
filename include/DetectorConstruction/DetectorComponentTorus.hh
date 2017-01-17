/*
 * DetectorComponentTorus.hh
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

#ifndef DETECTORCOMPONENTTORUS_HH
#define DETECTORCOMPONENTTORUS_HH

#include "DetectorComponent.hh"

class DetectorComponent_Torus : public DetectorComponent {
	
	/*
	 * 
	 * Class member variables
	 * 
	 * */

	public:
	
		G4double InnerRadius;
		G4double OuterRadius;
		G4double SweepingRadius;
		G4double PhiStart;
		G4double DeltaPhi;
		
	/*
	 * 
	 * Class member functions
	 * 
	 * */

	public:
	
		DetectorComponent_Torus(DetectorComponent_vars vars);
		~DetectorComponent_Torus();
	
		void ConstructVolume();
	
};

#endif
