/*
 * LuaPlugin.hh
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

#ifndef LUAPLUGIN_H
#define LUAPLUGIN_H

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
#include "DetectorConstruction.hh"
#include "Material.hh"
#include "Utilities.hh"

using std::cout;
using std::string;
using std::vector;

class LuaInstance {
	
	/*
	 * 
	 * Class member variables
	 * 
	 * */
	protected:
	
		lua_State *L;
		
		string Module_Path;
		string File;
		string File_Total_Path;
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		LuaInstance(string Module_Path, string File);
		~LuaInstance();
		
		void CloseLuaState();
		
	protected:
	
	
		/*
		* 
		* Functions include
		* 
		* lua_toboolean
		* lua_tolstring or lua_tostring (Read in the lua docs)
		* lua_tonumber
		* lua_tointeger
		* lua_tounsigned
		* 
		* Types include
		* 
		* LUA_TBOOLEAN
		* LUA_TNUMBER
		* LUA_TSTRING
		* 
		* */
		void LoadTable(string table);
		
		template<typename T, typename U>
		T GetGlobalVariable(string var,
		                    int VAR_TYPE,
		                    T DefaultValue,
                            U (*lua_Function)(lua_State *L, int index),
                            bool HaltExecution)
        {
			
			lua_getglobal(this->L, var.c_str());
			
			if (lua_type(this->L, -1) != VAR_TYPE) {
				
				cout << var << " wrong type\n";
				lua_pop(this->L, 1);
				if (HaltExecution) {
					
					cout << "Halting execution";
					exit(0);
					
				}
				return DefaultValue;
				
			}
			T ReturnValue = lua_Function(this->L, -1);
			lua_pop(this->L, 1);
			return ReturnValue;
			
		}
			
		template<typename T, typename U>
		T GetElementFromTable(string element, 
                              string ErrorMessage,
                              T DefaultValue,
                              int VAR_TYPE,
                              U (*lua_Function)(lua_State *L, int index),
                              bool HaltExecution)
                              
        {
			
			lua_pushstring(this->L, element.c_str());
			lua_gettable(this->L, -2);
	
			if (lua_type(this->L, -1) != VAR_TYPE) {
		
				cout << ErrorMessage << "\n";
				
				lua_pop(this->L, 1);
				if (HaltExecution == true)
					exit(0);
					
				return DefaultValue;
		
			}
			T ReturnValue = lua_Function(this->L, -1);
			lua_pop(this->L, 1);
			cout << element << " = " << ReturnValue << "\n";
			return ReturnValue;
			
		}
		G4ThreeVector GetG4ThreeVector(string TableName);
	
};










class ConfigLuaInstance : public LuaInstance {
	
	public:
	
		string modulename;
		G4VUserPhysicsList *physicslist;
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		ConfigLuaInstance(string ModulePath);
		~ConfigLuaInstance();
		
	private:
	
		void Initialize_modulename();
		void Initialize_physicslist();
	/*
	 * 
	 * TODO
	 * 
	 * Finish class
	 * 
	 * */
	
};









class DetectorConfigLuaInstance : public LuaInstance {
	
	
	/*
	 * 
	 * Class member variables
	 * 
	 * */
	public:
	
		int Number_of_Dectector_Components;
		DetectorComponent *World;
		vector<DetectorComponent *> Components;
		vector<DetectorComponent_Cylinder> CylinderComponents;
		vector<DetectorComponent_Box> BoxComponents;
		
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		DetectorConfigLuaInstance(string ModulePath);
		~DetectorConfigLuaInstance();
	
	private:
	
		void Initialize_world();
		void Initialize_number_of_detector_components();
		void Initialize_detector_components();
		
		DetectorComponent *WithVolumeGetDetectorComponent(G4String Volume_Type, G4String Name);
		
		DetectorComponent_Cylinder *MakeDetectorComponent_Cylinder(G4String Name);
		DetectorComponent_Box *MakeDetectorComponent_Box(G4String Name);
		
	/*
	 * 
	 * TODO
	 * 
	 * Finish class
	 * 
	 * */
	
};





class MaterialConfigLua : public LuaInstance {
	
	/*
	 * 
	 * 
	 * */
	public:
	
		vector<Material *> Materials;
		
	private:
	
		int NumberOfMaterials;
	
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
		Material *ConstructMaterial_ByDatabase();
		Material *ConstructMaterial_ByHand();
	
};

class ParticlesConfigLua : public LuaInstance {


	/*
	 * Class member variables
	 * 
	 * */
	private:
	
		bool FourVectorFile;
		bool FileHasPosition;
		bool FileHasParticleNames;
		
		string PrimaryParticle_Name;
		
		G4ThreeVector Position;
	 
	public:

		string ParticleFile;
		string ParticleFileType;
		
		vector<FourVector> FourVectors;

	/*
	 * Class member functions
	 * 
	 * */
	public:
	
		ParticlesConfigLua(string ModulePath);
		~ParticlesConfigLua();
	
	private:
	
		void Initialize_ParticleFile();
		void Initialize_ParticleFileType();
		void Parse_ParticleFileType();
		void Parse_ParticleFileType_FourVector();
		void ReadFile_FourVector();
	
};

#endif

