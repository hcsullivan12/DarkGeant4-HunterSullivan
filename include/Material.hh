/*
 * Material.hh
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

#ifndef ELEMENT_H
#define ELEMENT_H

#include "G4Material.hh"

class Material {
	
	public:
	
		Material(G4String name);
		Material(G4String name, G4double z, G4double a, G4double density);
		~Material();
		
	G4Material *GetMaterialPointer();
	
	private:
	
		G4String name;
		G4double z, a, density;
	
		G4Material *DefinedMaterial;
		
};

#endif

