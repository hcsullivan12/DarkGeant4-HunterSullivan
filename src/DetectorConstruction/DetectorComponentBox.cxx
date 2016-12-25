/*
 * DetectorComponentBox.cxx
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

#include "DetectorComponentBox.hh"

//Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"

DetectorComponent_Box::DetectorComponent_Box(
                              G4String Name,
                              G4double half_x,
                              G4double half_y,
                              G4double half_z,
                              G4ThreeVector Position,
                              G4String MaterialString,
                              G4String Inside)
 : DetectorComponent(Name, BOX, Position, MaterialString, Inside) 
{
	
	this->half_x = half_x;
	this->half_y = half_y;
	this->half_z = half_z;
	
}


DetectorComponent_Box::~DetectorComponent_Box() {
	

	
	
}

/*
 * DetectorComponent_Box::ConstructVolume
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void DetectorComponent_Box::ConstructVolume() {
	
	G4Box *VirtualVolume = new G4Box(this->Name,
                                     this->half_x * m,
                                     this->half_y * m,
                                     this->half_z * m);
                                     
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);
	
}

