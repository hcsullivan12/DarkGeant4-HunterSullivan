/*
 * DetectorConstruction.cxx
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

#include "DetectorConstruction.hh"

//Geant4
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"

using std::cout;

DetectorConstruction::DetectorConstruction() {
	
	this->Air         = new Material("G4_AIR");
    this->LiquidArgon = new Material("LiquidArgon", 18., 39.95 * g/mole,
														 1.390 * g/cm3);
	
}

DetectorConstruction::~DetectorConstruction() {



}

G4VPhysicalVolume* DetectorConstruction::Construct() {

	InitializeWorld();
	InitializeDetector();
	InitializePhysicalVolume();
	
	return this->WorldPhysicalVolume;
}

void DetectorConstruction::InitializeWorld() {

	G4double world_hx = 3.0*m;
	G4double world_hy = 1.0*m;
	G4double world_hz = 1.0*m;
	
	this->worldBox = new G4Box("World", world_hx, world_hy, world_hz);
	
	/*
	 * With the defined object, you can create an object with made
	 * out of a material or element. The following code is called a
	 * Logical Volume.
	 * 
	 * Need to specify what Ar and Al are!
	 * 
	 * */
	 
	this->worldLog = new G4LogicalVolume(this->worldBox, 
										 this->Air->GetMaterialPointer(), 
										 "World");
	
}

void DetectorConstruction::InitializeDetector() {
	
	/*
	 * Creates a cylinder of radius 60cm, with length (in the z direction)
	 * 50 cm. hz defines a half length.
	 * 
	 * */
	G4double innerRadius = 0.*cm;
	G4double outerRadius = 60.*cm;
	G4double hz = 25.*cm;
	G4double startAngle = 0.*deg;
	G4double spanningAngle = 360.*deg;
	
	this->trackerTube = new G4Tubs("Tracker",
									innerRadius,
									outerRadius,
									hz,
									startAngle,
									spanningAngle);
									
	/*
	 * With the defined object, you can create an object with made
	 * out of a material or element. The following code is called a
	 * Logical Volume.
	 * 
	 * Need to specify what Ar and Al are!
	 * 
	 * */									
	this->trackerLog = new G4LogicalVolume(this->trackerTube, 
										   this->LiquidArgon->GetMaterialPointer(), 
										   "Tracker");
	
}

void DetectorConstruction::InitializePhysicalVolume() {
	
	this->WorldPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(), 
										  this->worldLog, "World",
										  0, false, 0);
									
	G4VPhysicalVolume *TrackerPhysical = new G4PVPlacement(0, 
											 G4ThreeVector(), 
										     this->trackerLog,
										     "Detector",
										     this->worldLog,
										     false,
										     0);
	
	if (TrackerPhysical == NULL)
		cout << "Tracker physical volume could not be initialized\n";
	
}
