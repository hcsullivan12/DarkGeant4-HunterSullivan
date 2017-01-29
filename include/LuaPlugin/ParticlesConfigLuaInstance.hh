/*
 * ParticlesConfigLuaInstance
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

#ifndef PARTICLESCONFIGLUAINSTANCE_HH
#define PARTICLESCONFIGLUAINSTANCE_HH

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
#include "Utilities.hh"

using std::cout;
using std::string;
using std::vector;

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
		bool EnergyDefinedByFunction;
		
		string ParticleFile;
		string ParticleFileType;
		string PrimaryParticle_Name;
	 
	public:
		
		int NumberOfEvents;
		int PrimariesPerEvent;
		int TotalNumberOfPrimaries;
		
		vector<FourVector> *FourVectors;

	/*
	 * Class member functions
	 * 
	 * */
	public:
	
		ParticlesConfigLua(string ModulePath);
		~ParticlesConfigLua();
	
	private:
	
		bool CheckForFile();
	
		void Initialize_ParticleFile();
		void Initialize_ParticleFileType();
		void Initialize_ParticlePositions_byFunction();
		void Initialize_GenericFourVector();
		
		void Parse_ParticleFileType();
		void Parse_ParticlePosition();
		void Parse_ParticleEnergy();
		void Parse_ParticleTypes();
		void Parse_ParticleMomentum();
		void Parse_ParticleFileType_FourVector();
		
		void SetEnergyByRange();
		void SetEnergyByNumber();
		void SetEnergyByFunction();
		void SetPrimariesByString();
		void SetPrimariesByFunction();
		void SetMomentumByTable();
		void SetMomentumByFunction();
		
		void SetObjectVarsWithFileInformation();
		
		void Load_Function();
		void ReadFile_FourVector();
	
};

#endif

