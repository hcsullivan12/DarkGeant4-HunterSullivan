/*
 * DetectorConstructionV2.hh
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

#ifndef DETECTORCONSTRUCTIONV2_HH
#define DETECTORCONSTRUCTIONV2_HH

class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class UniformEMField;

//Geant4 Headers
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"

#include "G4ThreeVector.hh"
#include "G4VUserDetectorConstruction.hh"

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

// C/C++ headers
#include <vector>

//User Headers
#include "DetectorComponent.hh"
#include "Material.hh"
#include "UniformEMField.hh"

using std::vector;

class DetectorConstructionV2 : public G4VUserDetectorConstruction {
	
	/*
	 * Class member variables
	 * 
	 * */
	private:
	
		// Detector Components
		DetectorComponent *World;
		vector<DetectorComponent *> Components;
		vector<Material *> Materials;
		
		G4VPhysicalVolume *WorldPhysicalVolume;
	
	/*
	 * Class member functions
	 * 
	 * 
	 * */
	public:
	
		DetectorConstructionV2(DetectorComponent *World,
                               vector<DetectorComponent *> Components,
                               vector<Material *> Materials);
		~DetectorConstructionV2();
		
		G4VPhysicalVolume* Construct();
	
	private:
	
		void InitializeWorld();
		void InitializeDetectorComponents();
		void InitializePhysicalVolume();

		void InitializeWorldEMField();
		
		void FindMaterial(DetectorComponent *Component);
		
	
};

#endif

