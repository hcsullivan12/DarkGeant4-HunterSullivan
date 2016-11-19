/*
 * DetectorComponentEllipsoid.cxx
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


#include "DetectorComponentEllipsoid.hh"

//Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"

DetectorComponent_Ellipsoid::DetectorComponent_Ellipsoid(
				G4String Name,
                                G4double xSemiAxis,
                                G4double ySemiAxis,
                                G4double zSemiAxis,
                                G4double zBottom,
                                G4double zTop,
                                G4ThreeVector Position,
                                G4String MaterialString,
                                G4String Inside)
 : DetectorComponent(Name, Ellipsoid, Position, MaterialString, Inside)
{
	
	this->xSemiAxis = xSemiAxis;
	this->ySemiAxis = ySemiAxis;
	this->zSemiAxis = zSemiAxis;
	this->zBottom = zBottom;
	this->zTop = zTop;
	
}

DetectorComponent_Ellipsoid::~DetectorComponent_Ellipsoid() {
	
	
}

void DetectorComponent_Ellipsoid::ConstructVolume() {
	
	G4Ellipsoid *VirtualVolume = new G4Ellipsoid(this->Name,
                                       this->xSemiAxis * m,
                                       this->ySemiAxis * m,
                                       this->zSemiAxis * m,
                                       this->zBottom * m,
                                       this->zTop * m);
	
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);

}

