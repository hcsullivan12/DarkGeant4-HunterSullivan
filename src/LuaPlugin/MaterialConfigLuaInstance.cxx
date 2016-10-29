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
		
		cout << "Material_" + IterationString << "\n";
		if(GetBooleanFromTable_NoHalt("G4Database", 
           "No G4Database element found. Assuming False", 0))
        {
		
			Materials.push_back(ConstructMaterial_ByDatabase());
			
		} else {
		
			Materials.push_back(ConstructMaterial_ByHand());
			
		}
		
		lua_pop(this->L, 1);
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

