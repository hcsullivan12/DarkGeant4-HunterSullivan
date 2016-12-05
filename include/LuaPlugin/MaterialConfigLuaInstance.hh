/*
 * MaterialsConfigLuaInstance.hh
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

#ifndef MATERIALCONFIGLUAINSTANCE_HH
#define MATERIALCONFIGLUAINSTANCE_HH

// Third Party Headers
#include "lua.hpp"

// C/C++ Headers
#include <iostream>
#include <string>
#include <exception>
#include <vector>

// Geant 4 Headers
#include "G4VUserPhysicsList.hh"

// User Headers
#include "LuaInstance.hh"
#include "Material.hh"
#include "Utilities.hh"

using std::cout;
using std::string;
using std::vector;

class MaterialConfigLua : public LuaInstance {
	
	/*
	 * 
	 * 
	 * */
	public:
	
		vector<Material *> Materials;
		vector<Composite_Material *> Composite_Materials;
		
	private:
	
		int NumberOfMaterials;
		int NumberOfCompositeMaterials;
	
	/*
	 * Class member functions
	 * 
	 * 
	 * */
	public:
	
		MaterialConfigLua(string ModulePath);
		~MaterialConfigLua();
		
	private:
	
		void Initialize_NumberOfMaterials();
		void Initialize_MaterialsVector();
		void Initialize_CompositeMaterialsVector();
		
		void GetCompositeCompoments(G4int NumComponents,
                                    G4String *materials, 
                                    G4double *fracmass);
                                    
		G4double CalculateDensity(G4int NumComponents, G4double fracmass);
		
		Material *ConstructMaterial_ByDatabase();
		Material *ConstructMaterial_ByHand();
		
		Material *FindAppropriateMaterialPointer(G4String material);
		
		Composite_Material *ConstructCompositeMaterial();
	
};

#endif

