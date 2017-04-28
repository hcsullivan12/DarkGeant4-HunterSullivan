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

#include "UniformEMField.hh"

UniformEMField::UniformEMField(G4ThreeVector MagneticField, G4ThreeVector ElectricField) : G4ElectroMagneticField(){
	
	/* General field array stores components of Magnetic field in first three slots,
	 * Electric field in the last three slots 
	 * */

	this->MagneticField = MagneticField;
	this->ElectricField = ElectricField;
	
}

UniformEMField::~UniformEMField() {
	
}

void UniformEMField::GetFieldValue(const G4double Point[4], G4double* EMField) const {

	EMField[0] = this->MagneticField.x();
	EMField[1] = this->MagneticField.y();
	EMField[2] = this->MagneticField.z();
	
	EMField[3] = this->ElectricField.x();
	EMField[4] = this->ElectricField.y();
	EMField[5] = this->ElectricField.z();
	
}
