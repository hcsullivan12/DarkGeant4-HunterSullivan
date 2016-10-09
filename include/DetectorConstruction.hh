/*
 * DetectorConstruction.hh
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

#ifndef DETECTORCONSTRUCTION_H
#define DETECTORCONSTRUCTION_H

class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

//Geant4 Headers
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"

#include "G4ThreeVector.hh"
#include "G4VUserDetectorConstruction.hh"

// C/C++ headers
#include <vector>

//User Headers
#include "Material.hh"

using std::vector;

enum VolumeDefinition {

	WORLD = 0,
	DETECTOR_COMPONENT
	
};

enum VolumeType {

	BOX = 0,
	CYLINDER
	
};


void InitializeMaterials();

class DetectorConstruction : public G4VUserDetectorConstruction 
{

	/*
	 * 
	 * Class member variables
	 * 
	 * */
	private:
	
		G4Box *worldBox;
		G4Tubs *trackerTube;
		
		G4LogicalVolume *worldLog;
		G4LogicalVolume *trackerLog;
		
		G4VPhysicalVolume *WorldPhysicalVolume;
		
		Material *Air;
		Material *LiquidArgon;
		


	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		DetectorConstruction();
		~DetectorConstruction();
		
		G4VPhysicalVolume* Construct();
		
	private:
	
		void InitializeWorld();
		void InitializeDetector();
		void InitializePhysicalVolume();
		
};

class DetectorComponent {
	
	/*
	 * 
	 * Class member variables
	 * 
	 * */
	public:
	
		VolumeType Type;
		G4ThreeVector Position;
		Material *DetectorComponentMaterial;
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		DetectorComponent(VolumeType Type, 
                          G4ThreeVector Position,
                          G4String MaterialString);
		~DetectorComponent();
		
		
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

class DetectorComponent_Cylinder : public DetectorComponent {
	
	/*
	 * 
	 * Class member variables
	 * 
	 * */
	public:
	
		G4double InnerRadius;
		G4double OuterRadius;
		G4double StartAngle;
		G4double EndAngle;
		G4double HalfLength;
		
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		DetectorComponent_Cylinder(G4double InnerRadius,
                                   G4double OuterRadius,
                                   G4double StartAngle,
                                   G4double EndAngle,
                                   G4double HalfLength,
                                   G4ThreeVector Position,
                                   G4String MaterialString);
		~DetectorComponent_Cylinder();
	
};

class DetectorComponent_Box : public DetectorComponent {
	
	/*
	 * 
	 * Class member variables
	 * 
	 * */
	public:
	
		G4double x;
		G4double y;
		G4double z;
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		DetectorComponent_Box(G4double x,
                              G4double y,
                              G4double z,
                              G4ThreeVector Position,
                              G4String MaterialString);
		~DetectorComponent_Box();
	
};

#endif
