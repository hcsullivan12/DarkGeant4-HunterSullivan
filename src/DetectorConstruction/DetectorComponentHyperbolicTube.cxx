/*
 * DetectorComponentHyperbolicTube.cxx
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


#include "DetectorComponentHyperbolicTube.hh"

//Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4Hype.hh"
#include "G4LogicalVolume.hh"

DetectorComponent_HyperbolicTube::DetectorComponent_HyperbolicTube(
                                G4String Name,
								G4double InnerRadius;
								G4double OuterRadius;
								G4double InnerRadiusAngle;
								G4double OuterRadiusAngle;
								G4double zHalfLength;
                                G4ThreeVector Position,
                                G4String MaterialString,
                                G4String Inside)
 : DetectorComponent(Name, HYPERBOLIC_TUBE, Position, MaterialString, Inside)
{
	
	this->InnerRadius = InnerRadius;
	this->OuterRadius = OuterRadius;
	this->InnerRadiusAngle = InnerRadiusAngle;
	this->OuterRadiusAngle = OuterRadiusAngle;
	this->zHalfLength = zHalfLength;
	
}

DetectorComponent_HyperbolicTube::~DetectorComponent_HyperbolicTube() {
	
	
}


void DetectorComponent_HyperbolicTube::ConstructVolume() {
	
	G4Hype *VirtualVolume = new G4Hype(this->Name,
                                       this->InnerRadius * m,
                                       this->OuterRadius * m,
                                       this->InnerRadiusAngle * deg,
                                       this->OuterRadiusAngle * deg,
                                       this->zHalfLength * m);
	
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);

}

