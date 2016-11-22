/*
 * DetectorComponentTetrahedra.cxx
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

#include "DetectorComponentTetrahedra.hh"

//Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4Tet.hh"
#include "G4LogicalVolume.hh"

DetectorComponent_Tetrahedra::DetectorComponent_Tetrahedra(
				G4String Name,
				G4ThreeVector Point1,
				G4ThreeVector Point2,
				G4ThreeVector Point3,
				G4ThreeVector Point4,                          
                              	G4ThreeVector Position,
                              	G4String MaterialString,
                              	G4String Inside)
 : DetectorComponent(Name, TETRAHEDRA, Position, MaterialString, Inside) 
{
	
	this->Point1 = Point1;
	this->Point2 = Point2;
	this->Point3 = Point3;
	this->Point4 = Point4;
	
}


DetectorComponent_Tetrahedra::~DetectorComponent_Tetrahedra() {
	

	
	
}

void DetectorComponent_Tetrahedra::ConstructVolume() {
	
	G4Tet *VirtualVolume = new G4Tet(this->Name,
                                this->Point1 * m,
				this->Point2 * m,
				this->Point3 * m,
                                this->Point4 * m);
                                     
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);
	
}

