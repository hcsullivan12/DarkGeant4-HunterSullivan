/*
 * DetectorComponentTwistedBox.cxx
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

#include "DetectorComponentTwistedBox.hh"

//Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4TwistedBox.hh"
#include "G4LogicalVolume.hh"

DetectorComponent_TwistedBox::DetectorComponent_TwistedBox(
				G4String Name,
				G4double TwistingAngle,
				G4double xHalflength,
				G4double yHalfLength,
				G4double zHalfLength,                            
                                G4ThreeVector Position,
                                G4String MaterialString,
                                G4String Inside)
 : DetectorComponent(Name, TWISTED_BOX, Position, MaterialString, Inside) 
{
	
	this->TwistingAngle = TwistingAngle;
	this->xHalflength = xHalflength;
	this->yHalfLength = yHalfLength;
	this->zHalfLength = zHalfLength;
	
}


DetectorComponent_TwistedBox::~DetectorComponent_TwistedBox() {
	

	
	
}

void DetectorComponent_TwistedBox::ConstructVolume() {
	
	G4TwistedBox *VirtualVolume = new G4TwistedBox(this->Name,
					this->TwistingAngle * deg,
                                        this->xHalflength * m,
					this->yHalfLength * m,
                                        this->zHalfLength * m);
                                     
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);
	
}

