/*
 * DetectorComponentCylinder.cxx
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


#include "DetectorComponentCylinder.hh"

//Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"

DetectorComponent_Cylinder::DetectorComponent_Cylinder(DetectorComponent_vars vars)
 : DetectorComponent(vars)
{
	
	this->InnerRadius = vars.cylinder->InnerRadius;
	this->OuterRadius = vars.cylinder->OuterRadius;
	this->StartAngle  = vars.cylinder->StartAngle;
	this->HalfLength  = vars.cylinder->HalfLength;
	this->DeltaAngle  = vars.cylinder->DeltaAngle;
	
	delete vars.cylinder;
}

DetectorComponent_Cylinder::~DetectorComponent_Cylinder() {
	
	
}


/*
 * DetectorComponent_Cylinder::ConstructVolume
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void DetectorComponent_Cylinder::ConstructVolume() {
	
	G4Tubs *VirtualVolume = new G4Tubs(this->Name,
                                       this->InnerRadius * m,
                                       this->OuterRadius * m,
                                       this->HalfLength * m,
                                       this->StartAngle * deg,
                                       this->DeltaAngle * deg);
	
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name);

}

