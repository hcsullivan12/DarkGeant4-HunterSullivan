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
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"

DetectorComponent_Cone::DetectorComponent_Cone{G4String Name;
				G4double InnerRadiusAtTop,
				G4double InnerRadiusAtBottom,
				G4double OutsideRadiusAtTop,
				G4double OutsideRadiusAtBottom,
				G4double HalfLength,
				G4double StartAngle,
				G4double DeltaAngle,
				G4ThreeVector Position,
				G4String MaterialString,
				G4String Inside)
 : DetectorComponent(Name, CONE, Position, MaterialString, Inside)
{
		this->InnerRadiusAtTop = InnerRadiusAtTop;
		this->InnerRadiusAtBottom = InnerRadiusAtBottom;
		this->OutsideRadiusAtTop = OutsideRadiusAtTop;
		this->OutsideRadiusAtBottom = OutsideRadiusAtBottom;
		this->HalfLength = HalfLength;	
		this->StartAngle = StartAngle;
		this->DeltaAngle = DeltaAngle;

}

void DetectorComponent_Cone::ConstructVolume() {

	G4Cons *VirtualVolume = new G4Cons(this->Name,
					this->InnerRadiusAtTop * m,
					this->InnerRadiusAtBottom * m,
					this->OutsideRadiusAtTop * m,
					this->OutsideRadiusAtBottom * m,
					this->HalfLength * m,
					this->StartAngle * deg,
					this->DeltaAngle * deg);		
	
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);


}









