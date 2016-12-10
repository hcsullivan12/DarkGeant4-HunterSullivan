/*
 * DetectorComponentSphericalShell.cxx
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

#include "DetectorComponentSphericalShell.hh"

//Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"

DetectorComponent_SphericalShell::DetectorComponent_SphericalShell(
			G4String Name,
                        G4double InnerRadius,
			G4double OuterRadius,
			G4double PhiStart,
			G4double DeltaPhi,
			G4double ThetaStart,
			G4double DeltaTheta,
                        G4ThreeVector Position,
                        G4String MaterialString,
                        G4String Inside)
 : DetectorComponent(Name, SPHERICAL_SHELL, Position, MaterialString, Inside) 
{
	
	this->InnerRadius = InnerRadius;
	this->OuterRadius = OuterRadius;
	this->PhiStart = PhiStart;
	this->DeltaPhi = DeltaPhi;
	this->ThetaStart = ThetaStart;
	this->DeltaTheta = DeltaTheta;
	
}


DetectorComponent_SphericalShell::~DetectorComponent_SphericalShell() {
	

	
	
}

void DetectorComponent_SphericalShell::ConstructVolume() {
	
	G4Sphere *VirtualVolume = new G4Sphere(this->Name,
					this->InnerRadius * m,
                                        this->OuterRadius * m,
					this->PhiStart * rad,
					this->DeltaPhi * rad,
                                        this->ThetaStart * rad,
					this->DeltaTheta * rad);
                                     
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);
	
}
