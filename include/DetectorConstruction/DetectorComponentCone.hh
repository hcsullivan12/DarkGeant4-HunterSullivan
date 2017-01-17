/*
 * DetectorComponentCone.hh
 * 
 * Copyright 2016 Emma Davenport <Davenport.physics@gmail.com>
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

#ifndef DETECTORCOMPONENTCONE_HH
#define DETECTORCOMPONENTCONE_HH

#include "DetectorComponent.hh"

class DetectorComponent_Cone : public DetectorComponent {

	/*
 	 * Class Member Variables
	 *
	 * */
	public:
		G4double InnerRadiusAtBottom;
		G4double OutsideRadiusAtBottom;
		G4double InnerRadiusAtTop;
		G4double OutsideRadiusAtTop;
		G4double HalfLength;
		G4double StartAngle;
		G4double DeltaAngle;
	
	/*
	 * Public Class Member functions
	 * 
	 * */
	 public:
		//Constructor
		DetectorComponent_Cone(DetectorComponent_vars vars);
		~DetectorComponent_Cone();
		
		void ConstructVolume();
	
};

#endif

