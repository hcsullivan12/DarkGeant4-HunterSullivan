/*
 * DetectorComponentEllipticalCone.cxx
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


#include "DetectorComponentEllipticalCone.hh"

//Geant4 Headers
#include "G4SystemOfUnits.hh"
#include "G4EllipticalCone.hh"
#include "G4LogicalVolume.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"

using std::cout;

DetectorComponent_EllipticalCone::DetectorComponent_EllipticalCone(DetectorComponent_vars vars)
 : DetectorComponent(vars)
{
	
	this->xSemiAxis = vars.elliptical_cone->xSemiAxis;
	this->ySemiAxis = vars.elliptical_cone->ySemiAxis;
	this->Height    = vars.elliptical_cone->Height;
	this->zTop      = vars.elliptical_cone->zTop;
	
	delete vars.elliptical_cone;
}

DetectorComponent_EllipticalCone::~DetectorComponent_EllipticalCone() {
	
	
}

void DetectorComponent_EllipticalCone::ConstructVolume() {
	
	G4EllipticalCone *VirtualVolume = new G4EllipticalCone(this->Name,
                    this->xSemiAxis * m,
                    this->ySemiAxis * m,
                    this->Height * m,
                    this->zTop * m);

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

bool DetectorComponent_EllipticalCone::WithinVolume(G4double x, G4double y, G4double z) {

	cout << "DetectorComponent_EllipticalCone WithinVolume STUB\n";

	return true;
	
}
