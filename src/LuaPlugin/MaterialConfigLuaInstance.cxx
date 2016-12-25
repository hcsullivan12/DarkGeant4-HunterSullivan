/*
 * MaterialConfigLuaInstance.cxx
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

#include "MaterialConfigLuaInstance.hh"

#include "G4SystemOfUnits.hh"

MaterialConfigLua::MaterialConfigLua(string ModulePath)
 : LuaInstance(ModulePath, "Materials.lua") 
{
	
	Initialize_NumberOfMaterials();
	Initialize_MaterialsVector();
	Initialize_CompositeMaterialsVector();
	
}


MaterialConfigLua::~MaterialConfigLua() {
	
	
	
}

/*
 * Initialize_NumberOfMaterials()
 * 
 * * Description
 * 
 *		...
 * 
 * 
 * */

void MaterialConfigLua::Initialize_NumberOfMaterials() {
	
	this->NumberOfMaterials = GetIntegerFromGlobal_WithHalt(
	                                             "Number_Of_Materials");
	
	this->NumberOfCompositeMaterials = GetIntegerFromGlobal_NoHalt(
                                        "Number_Of_Composite_Materials",
                                        0);
}

/*
 * Initialize_MaterialsVector()
 * 
 * * Description
 * 
 * 		...
 * 
 * 
 * */

void MaterialConfigLua::Initialize_MaterialsVector() {
	
	for (int i = 1; i <= this->NumberOfMaterials;i++) {
	
		string IterationString = ConvertIntToString(i);
		LoadTable("Material_" + IterationString);
		
		if (!IsTableElementNil("G4Name")) {
			
			this->Materials.push_back(ConstructMaterial_ByDatabase());
			
		} else {
			
			this->Materials.push_back(ConstructMaterial_ByHand());
		
		}
		
		lua_pop(this->L, 1);
		cout << "\n";
	}
	
}

void MaterialConfigLua::Initialize_CompositeMaterialsVector() {

	for (int i = 1;i <= this->NumberOfCompositeMaterials;i++) {
	
		string IterationString = ConvertIntToString(i);
		LoadTable("Composite_Material_" + IterationString);
		
		cout << "Composite_Material_" + IterationString << "\n";
		
		this->Composite_Materials.push_back(ConstructCompositeMaterial());
		
		// Pops Table
		lua_pop(this->L, 1);
		cout << "\n";
	}
	
}

/*
 * ConstructMaterial_ByDatabase()
 * 
 * * Description
 * 
 * 		...
 * 
 * */

Material *MaterialConfigLua::ConstructMaterial_ByDatabase() {

	G4String DatabaseName = GetStringFromTable_WithHalt("G4Name",
                                "Make sure you have a G4Name variable!"
                                + string(" Halting Execution.\n"));
	
	return new Material(DatabaseName);
	
}

/*
 * ConstructMaterial_ByHand()
 * 
 * * Description
 * 
 * 		...
 * 
 * */

Material *MaterialConfigLua::ConstructMaterial_ByHand() {
	
	G4String Name = GetStringFromTable_WithHalt("Name",
                                "Make sure you have a Name variable!"
                                + string(" Halting execution.\n"));
                                
	G4double NumberOfProtons = GetNumberFromTable_WithHalt(
	                  "Number_Of_Protons",
	                  "Make sure you have a Number_Of_Protons variable!"
	                  + string(" Halting execution.\n"));
	                        
	G4double AtomicMass = GetNumberFromTable_WithHalt("Atomic_Mass",
	                      "Make sure you have a Atomic_Mass variable!"
	                      + string(" Halting execution.\n"));
	                      
	G4double Density = GetNumberFromTable_WithHalt("Density",
                          "Make sure you have a Density variable!"
                          + string(" Halting execution.\n"));
	
	return new Material(Name, 
                        NumberOfProtons, 
                        AtomicMass * g/mole, 
                        Density * g/cm3);
	
}

Composite_Material *MaterialConfigLua::ConstructCompositeMaterial() {

	G4String Name = GetStringFromTable_WithHalt("Name",
                                "Make sure you have a Name variable!"
                                + string(" Halting execution.\n"));
	
	G4int NumberOfComponents = GetIntegerFromTable_WithHalt(
                                  "Number_Of_Components",
                                  "Number_Of_Components not specified");
                                                
    if (NumberOfComponents <= 0) {
	
		cout << "Number of components should be greater than 0!\n";
		exit(1);
		
	}
	//Gets Components from Component_x tables
	G4String *materials = new G4String[NumberOfComponents];
	G4double *fracmass  = new G4double[NumberOfComponents];
	GetCompositeCompoments(NumberOfComponents, materials, fracmass);
	
	
	vector<Material *> MaterialsVec;
	vector<G4double >  FracmassVec;
	
	for (int i = 0;i < NumberOfComponents;i++) {
	
		MaterialsVec.push_back(FindAppropriateMaterialPointer(materials[i]));
		FracmassVec.push_back(fracmass[i]);
		
	}
	
	G4double Density = GetNumberFromTable_NoHalt("Density", 
                                      "Density will be calculated",
                                      -1.0);
                                      
	if (Density <= 0) {
	
		//Call G4double CalculateDensity(G4int NumComponents, G4double fracmass);
		
	}
	
	delete [] materials;
	delete [] fracmass;
	
	return NULL;
}

void MaterialConfigLua::GetCompositeCompoments(G4int NumComponents,
                                               G4String *materials, 
                                               G4double *fracmass) 
{
	
	for (G4int i = 1; i <= NumComponents;i++) {
	
		string ItrString = ConvertIntToString(i);
		LoadTable_WithinTable("Component_" + ItrString);
		
		cout << "Component_" + ItrString << "\n";
		
		materials[i-1] = GetStringFromTable_WithHalt("Material",
                                              "No Material specified");
		fracmass[i-1]  = GetNumberFromTable_WithHalt("Fractional_Mass",
                                        "No Fractional_Mass specified");
	
		//pops table
		lua_pop(this->L, 1);
	}
	
}

Material *MaterialConfigLua::FindAppropriateMaterialPointer(G4String material) {

	for (size_t i = 0;i < this->Materials.size();i++) {
	
		if (material == Materials[i]->GetMaterialName()) {
		
			return Materials[i];
			
		}
		
	}
	
	cout << material << " not defined\n";
	throw;
	
}
