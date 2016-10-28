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
		bool PositionDefinedByFunction;
		
		string ParticleFile;
		string ParticleFileType;
		string PrimaryParticle_Name;
		
		G4ThreeVector Position;
	 
	public:
		
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
		void Initialize_ParticlePositions_byFunction();
		
		void Parse_ParticleFileType();
		void Parse_ParticlePosition();
		void Parse_ParticleFileType_FourVector();
		
		void Load_PositionFunction();
		
		void ReadFile_FourVector();
	
};

#endif

