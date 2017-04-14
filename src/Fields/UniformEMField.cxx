/*
 * UniformEMField.cxx
 * 
 * Copyright 2017 Hunter Sullivan <hunter.sullivan@mavs.uta.edu>
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

#include "G4ThreeVector.hh"
#include "UniformEMField.hh"
#include "G4EqMagElectricField.hh"
#include "G4ClassicalRK4.hh"
#include "G4ChordFinder.hh"
#include "G4FieldManager.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4ChordFinder.hh"

UniformEMField::UniformEMField(G4ThreeVector MagneticField, G4ThreeVector ElectricField) {
	
	/* General field array stores components of Magnetic field in first three slots,
	 * Electric field in the last three slots 
	 * */
	
	field[0] = MagneticField.x();
	field[1] = MagneticField.y();
	field[2] = MagneticField.z();
	
	field[3] = ElectricField.x();
	field[4] = ElectricField.y();
	field[5] = ElectricField.z();
	
}

UniformEMField::~UniformEMField() {
	
}

void UniformEMField::ConstructField(string Name) {
	
	if (Name == "World") {
		G4EqMagElectricField* Equation = new G4EqMagElectricField(field);
		
		G4FieldManager* FieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
		FieldMgr->SetFieldChangesEnergy(true);
		
		G4MagIntegratorStepper* Stepper = new G4ClassicalRK4(Equation,8);
		
		fieldMgr->SetDetectorField(field);
		
		G4ChordFinder* ChordFinder = new G4ChordFinder(field, 0.01*mm, Stepper);
		FieldMgr->SetChordFinder(ChordFinder);
	}
}
