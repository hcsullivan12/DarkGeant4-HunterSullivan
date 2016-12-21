/*
 * DetectorComponentCone.cxx
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

#include "DetectorComponentCone.hh"

//Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"

DetectorComponent_Cone::DetectorComponent_Cone(G4String Name,
				G4double InnerRadiusAtBottom,
				G4double OutsideRadiusAtBottom,
				G4double InnerRadiusAtTop,
				G4double OutsideRadiusAtTop,
				G4double HalfLength,
				G4double StartAngle,
				G4double DeltaAngle,
				G4ThreeVector Position,
				G4String MaterialString,
				G4String Inside)
 : DetectorComponent(Name, CONE, Position, MaterialString, Inside)
{
		this->InnerRadiusAtBottom = InnerRadiusAtBottom;
		this->OutsideRadiusAtBottom = OutsideRadiusAtBottom;
		this->InnerRadiusAtTop = InnerRadiusAtTop;
		this->OutsideRadiusAtTop = OutsideRadiusAtTop;
		this->HalfLength = HalfLength;	
		this->StartAngle = StartAngle;
		this->DeltaAngle = DeltaAngle;

}

DetectorComponent_Cone::~DetectorComponent_Cone() {
	

	
	
}

void DetectorComponent_Cone::ConstructVolume() {

	G4Cons *VirtualVolume = new G4Cons(this->Name,
					this->InnerRadiusAtBottom * m,
					this->OutsideRadiusAtBottom * m,
					this->InnerRadiusAtTop * m,
					this->OutsideRadiusAtTop * m,
					this->HalfLength * m,
					this->StartAngle * deg,
					this->DeltaAngle * deg);		
	
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);


}









