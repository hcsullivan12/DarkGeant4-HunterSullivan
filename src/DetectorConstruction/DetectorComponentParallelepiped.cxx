/*
 * DetectorComponentParallelepiped.cxx
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


#include "DetectorComponentParallelepiped.hh"

//Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4Para.hh"
#include "G4LogicalVolume.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"

using std::cout;

DetectorComponent_Parallelepiped::DetectorComponent_Parallelepiped(DetectorComponent_vars vars)
 : DetectorComponent(vars)
{
	
	this->xHalfLength             = vars.parallelepiped->xHalfLength;
	this->yHalfLength             = vars.parallelepiped->yHalfLength;
	this->zHalfLength             = vars.parallelepiped->zHalfLength;
	this->AngleOfXZFaces          = vars.parallelepiped->AngleOfXZFaces;
	this->PolarAngleOfXYFaces     = vars.parallelepiped->PolarAngleOfXYFaces;
	this->AzimuthalAngleOfXYFaces = vars.parallelepiped->AzimuthalAngleOfXYFaces;
	
	delete vars.parallelepiped;
}

DetectorComponent_Parallelepiped::~DetectorComponent_Parallelepiped() {
	
	
}

void DetectorComponent_Parallelepiped::ConstructVolume() {
	
	G4Para *VirtualVolume = new G4Para(this->Name,
	                                   this->xHalfLength * m,
                                       this->yHalfLength * m,
                                       this->zHalfLength * m,
                                       this->AngleOfXZFaces * deg,
                                       this->PolarAngleOfXYFaces * deg,
                                       this->AzimuthalAngleOfXYFaces * deg);

	G4UniformMagField* magField =new G4UniformMagField(this->MagneticField);
        //G4Mag_UsualEqRhs* myEquation = new G4Mag_UsualEqRhs(magField);
        //G4MagIntegratorStepper* myStepper = new G4ClassicalRK4(myEquation);
       // G4ChordFinder* myChordFinder = new G4ChordFinder(magField,1.0e-5*mm,myStepper);
        G4FieldManager* fieldMgr = new G4FieldManager(magField);
	
	this->LogicalVolume = new G4LogicalVolume(VirtualVolume,
                 this->DetectorComponentMaterial->GetMaterialPointer(),
                 this->Name,
		 fieldMgr);

}

bool DetectorComponent_Parallelepiped::WithinVolume(G4double x, G4double y, G4double z) {

	cout << "DetectorComponent_Parallelepiped WithinVolume STUB\n";

	return true;
	
}

