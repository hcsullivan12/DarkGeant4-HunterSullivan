/*
 * DetectorComponent.hh
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

#ifndef DETECTORCOMPONENT_HH
#define DETECTORCOMPONENT_HH

class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

//Geant4 Headers
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"

#include "G4ThreeVector.hh"

// C/C++ headers
#include <vector>

//User Headers
#include "Material.hh"

enum VolumeType {

	BOX = 0,
	CYLINDER,
	CONE,
	ELLIPSOID,
	ELLIPTICAL_CONE,
	ELLIPTICAL_TUBE,
	HYPERBOLIC_TUBE,
	PARALLELEPIPED,
	SOLID_SPHERE,
	SPHERICAL_SHELL,
	TETRAHEDRA,
	TORUS,
	TRAPEZOID,
	TWISTED_BOX
	
};

class DetectorComponent {
	
	/*
	 * 
	 * Class member variables
	 * 
	 * */
	public:
	
		G4String Name;
		VolumeType Type;
		G4ThreeVector Position;
		G4String MaterialString;
		Material *DetectorComponentMaterial;
		G4String Inside;
		G4LogicalVolume *LogicalVolume;
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		DetectorComponent(G4String Name,
		                  VolumeType Type, 
                          G4ThreeVector Position,
                          G4String MaterialString,
                          G4String Inside);
		~DetectorComponent();
		
		virtual void ConstructVolume() {;}
		
	protected:
	
		void SetMaterialPointer(G4String MaterialString);
	
	/*
	 * 
	 * TODO
	 * 
	 * 		Finish this class
	 * 
	 * */
	
};

#endif
