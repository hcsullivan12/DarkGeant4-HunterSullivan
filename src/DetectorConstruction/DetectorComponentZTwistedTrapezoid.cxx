/*
 * DetectorComponentZTwistedTrapezoid.cxx
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


#include "DetectorComponentZTwistedTrapezoid.hh"

//Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4TwistedTrd.hh"
#include "G4LogicalVolume.hh"

DetectorComponent_ZTwistedTrapezoid::DetectorComponent_ZTwistedTrapezoid(
					G4String Name,
					G4double xHalfLengthAtBottom,
					G4double xHalfLengthAtTop,
					G4double yHalfLengthAtBottom,
					G4double yHalfLengthAtTop,
					G4double zHalfLength,
					G4double TwistingAngle,
                                  	G4ThreeVector Position,
                                   	G4String MaterialString,
                                  	G4String Inside)
 : DetectorComponent(Name, Z_TWISTED_TRAPEZOID, Position, MaterialString, Inside)
{
	
	this->xHalfLengthAtBottom = xHalfLengthAtBottom;
	this->xHalfLengthAtTop = xHalfLengthAtTop;
	this->yHalfLengthAtBottom = yHalfLengthAtBottom;
	this->yHalfLengthAtTop = yHalfLengthAtTop;
	this->zHalfLength = zHalfLength;
	this->TwistingAngle = TwistingAngle;
	
}

DetectorComponent_ZTwistedTrapezoid::~DetectorComponent_ZTwistedTrapezoid() {
	
	
}

void DetectorComponent_ZTwistedTrapezoid::ConstructVolume() {
	
	G4TwistedTrd *VirtualVolume = new G4TwistedTrd(this->Name,
                                        this->xHalfLengthAtBottom * m,
                                        this->xHalfLengthAtTop * m,
                                        this->yHalfLengthAtBottom * m,
                                        this->yHalfLengthAtTop * m,
					this->zHalfLength * m
                                        this->TwistingAngle * deg);
	
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);

}

