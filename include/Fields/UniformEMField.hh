/*
 * UniformEMField.hh
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

#ifndef UNIFORMEMFIELD_HH
#define UNIFORMEMFIELD_HH

#include "G4ElectroMagneticField.hh"
#include "G4ThreeVector.hh"

class UniformEMField : public G4ElectroMagneticField {
	
    /*
     * 
     * Class member variables
     * 
     * */
     
     public:
		
		G4ThreeVector MagneticField;
		G4ThreeVector ElectricField;
		
     
    /*
     * 
     * Class member functions
     * 
     * */
     
     public:
		UniformEMField(G4ThreeVector MagneticField, G4ThreeVector ElectricField);
		virtual ~UniformEMField();
		
		virtual G4bool DoesFieldChangeEnergy() const { return true; };
		
		virtual void GetFieldValue(const G4double Point[4], G4double* EMField) const;
};

#endif
