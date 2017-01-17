/*
 * DetectorComponentTorus.cxx
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

#include "DetectorComponentTorus.hh"

//Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4Torus.hh"
#include "G4LogicalVolume.hh"

DetectorComponent_Torus::DetectorComponent_Torus(DetectorComponent_vars vars)
 : DetectorComponent(vars) 
{
	
	this->InnerRadius    = vars.torus->InnerRadius;
	this->OuterRadius    = vars.torus->OuterRadius;
	this->SweepingRadius = vars.torus->SweepingRadius;
	this->PhiStart       = vars.torus->PhiStart;
	this->DeltaPhi       = vars.torus->DeltaPhi;
	
	delete vars.torus;
}


DetectorComponent_Torus::~DetectorComponent_Torus() {
	

	
	
}

void DetectorComponent_Torus::ConstructVolume() {
	
	G4Torus *VirtualVolume = new G4Torus(this->Name,
                                        this->InnerRadius * m,
                                        this->OuterRadius * m,
					this->SweepingRadius * m,
					this->PhiStart * deg,
                                        this->DeltaPhi * deg);
                                     
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);
	
}

