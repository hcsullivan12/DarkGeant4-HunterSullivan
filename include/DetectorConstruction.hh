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

struct Volume {
	
	VolumeType Type;
	VolumeDefinition Definition;
	
	//Generic Volume Vars
	G4String name;
	Material ThisMaterial;
	
	//Box Vars
	G4double x;
	G4double y;
	G4double z;
	
	//Cylinder Vars
	G4double InnerRadius;
	G4double OuterRadius;
	G4double Half_z;
	G4double StartAngle;
	G4double EndAngle;
	
};

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
		
		vector<Volume> Volumes;


	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		DetectorConstruction();
		DetectorConstruction(vector<Volume> Volumes);
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
	 * Class member functions
	 * 
	 * */
	public:
	
		DetectorComponent();
		~DetectorComponent();
	
	/*
	 * 
	 * TODO
	 * 
	 * 		Finish this class
	 * 
	 * */
	
};

#endif
