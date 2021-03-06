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

#include "ParticlesConfigLuaInstance.hh"

#include <cstdlib>
#include <ctime>

#include "G4SystemOfUnits.hh"

ParticlesConfigLua::ParticlesConfigLua(string ModulePath) 
 : LuaInstance(ModulePath, "Particles.lua")
{
	
	srand(time(NULL));
	
	this->PrimariesPerEvent = 1;
	
	this->FourVectorFile            = false;
	this->FileHasPosition           = false;
	this->FileHasParticleNames      = false;
	this->PositionDefinedByFunction = false;
	
	if (CheckForFile()) {
		
		if (this->FourVectorFile) {
			
			cout << "Reading Four Vector File " << this->ParticleFile << "\n";
			ReadFile_FourVector();
			
		}
		
	} else {
		
		Initialize_GenericFourVector();
		Parse_ParticleEnergy();
		Parse_ParticleMomentum();
		Parse_ParticlePosition();
		Parse_ParticleTypes();
		
	}
	
}

ParticlesConfigLua::~ParticlesConfigLua() {
	
	delete [] this->FourVectors;
	
}

bool ParticlesConfigLua::CheckForFile() {

	this->ParticleFile = GetStringFromGlobal_NoHalt("Particle_File", "");
	if (this->ParticleFile.length() == 0) {
		
		cout << "Particle_File not defined\n";
		return false;
		
	}
		
	this->ParticleFileType = GetStringFromGlobal_WithHalt(
                                                  "Particle_File_Type");
	Parse_ParticleFileType();
    
	return true;
    
}

/*
 * Parse_ParticleFileType()
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void ParticlesConfigLua::Parse_ParticleFileType() {
	
	if (this->ParticleFileType.find("Four Vector") != std::string::npos) {
		
		this->FourVectorFile = true;
		Parse_ParticleFileType_FourVector();
		
	}
	
}

/*
 * Parse_ParticleFileType_FourVector()
 * 
 * * Description
 * 
 * 		If this->ParticleFileType was determined to contain the string
 * 		"Four Vector" then this function is called to determine
 * 		whether this->ParticleFileType has other attributes.
 * 
 * */

void ParticlesConfigLua::Parse_ParticleFileType_FourVector() {
	
	/*
	 * Determines whether the string "with name" can be found
	 * within the string this->ParticleFileType.
	 * 
	 * If it doesn't find the string "with name", the user is expected
	 * to give the name of the particles via the lua script.
	 * 
	 * */
	 
	if (this->ParticleFileType.find("with name") != std::string::npos) {
		
		this->FileHasParticleNames = true;
		
	}
	/*
	 * Determines whether the string "with position" can be found
	 * within the string this->ParticleFileType.
	 * 
	 * If it doesn't find the string "with position", the user is
	 * expected to give the position of the particles via the lua
	 * script.
	 * 
	 * */
	if (this->ParticleFileType.find("with position") != std::string::npos) {
		
		this->FileHasPosition = true;
		
	}
	
}

/*
 * Initialize_ParticlePositions_ByFunction()
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void ParticlesConfigLua::Initialize_ParticlePositions_byFunction() {
	
	Load_Function();
	
	for (int i = 1; i <= this->NumberOfEvents; i++) {
		
		for (int j = 0; j < this->PrimariesPerEvent;j++) {
		G4double *PositionPointers[3] = {&this->FourVectors[i-1][j].X,
                                         &this->FourVectors[i-1][j].Y,
                                         &this->FourVectors[i-1][j].Z};
                                         
			lua_pushinteger(this->L, this->PrimariesPerEvent * (i-1) + 1 + j);
			lua_gettable(this->L, -2);
                                         
			for (int k = 1; k <= 3; k++) {
		
				lua_pushinteger(this->L, k);
				lua_gettable(this->L, -2);
			
				if (lua_type(this->L, -1) != LUA_TNUMBER) {
			
					//DO something
				
				}
				*(PositionPointers[k-1]) = lua_tonumber(this->L, -1);
				//Pops value
				lua_pop(this->L, 1);
			
			}
			//Pops table
			lua_pop(this->L, 1);
		}
		
	}
	
	// Pops Particle_Table
	lua_pop(this->L, 1);
}

void ParticlesConfigLua::Initialize_GenericFourVector() {

	cout << "\nParticle_Table\n";
	LoadTable("Particle_Table");
                                             
	this->NumberOfEvents = GetIntegerFromTable_WithHalt("Number_Of_Events",
                                         "Number_Of_Events not found.");
                                         
	this->PrimariesPerEvent = GetIntegerFromTable_NoHalt("Primaries_Per_Event",
                                                         "Primaries_Per_Event set to 1",
                                                         1);
                                                         
	this->TotalNumberOfPrimaries = this->PrimariesPerEvent * this->NumberOfEvents;
	//Pops Particle_Table
	lua_pop(this->L, 1);
	
	this->FourVectors = new vector<FourVector>[this->NumberOfEvents];
	
	FourVector Vector;
	
	for (int i = 0;i < this->NumberOfEvents;i++) {
	
		for (int j = 0;j < this->PrimariesPerEvent; j++) {
			
			this->FourVectors[i].push_back(Vector);
			
		}
		
	}
	
}

void ParticlesConfigLua::Load_Function() {
	
	cout << "Function\n";
	// Pushes how many elements we want to generate.
	lua_pushinteger(this->L, this->TotalNumberOfPrimaries);
	
	if (lua_pcall(this->L, 1, 1, 0) != 0) {
	
		cout << "Error running function " << lua_tostring(this->L, -1);
		exit(0);
		
	}
	
	if (lua_type(this->L, -1) != LUA_TTABLE) {
		
		cout << "Expecting to obtain a table after calling position";
		cout << " function.";
		exit(0);
			
	}
	cout << "Loaded function\n";
	
}

/*
 * Parse_ParticlePosition()
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void ParticlesConfigLua::Parse_ParticlePosition() {

	LoadTable("Particle_Table");
	lua_pushstring(this->L, "Particles_Position");
	lua_gettable(this->L, -2);
	
	switch (lua_type(this->L, -1)) {
	
		case LUA_TTABLE:
		{
			/*
			 * Position table is at top of stack but GetG4ThreeVector
			 * assumes that Position isn't loaded so we have to pop
			 * it before calling GetG4ThreeVector("Particles_Position")
			 * 
			 * */
			cout << "LUA_TTABLE switch\n";
			lua_pop(this->L, 1);
			
			// Normally I would pass the 'm' constant defined by the G4SystemOfUnits, but
			// that results in a bug. So instead I simply just multiply the thing by 1.0,
			// effectively resulting in no conversion.
			G4ThreeVector Position = GetG4ThreeVector("Particles_Position", 1.0);
		
			for (int i = 0;i < this->NumberOfEvents;i++) {
				
				for (int j = 0;j < this->PrimariesPerEvent;j++) {
				
					this->FourVectors[i][j].X = Position.x();
					this->FourVectors[i][j].Y = Position.y();
					this->FourVectors[i][j].Z = Position.z();
				}
				
			}
			lua_pushnil(this->L);
		}
		break;
		case LUA_TFUNCTION:
		
			cout << "LUA_TFUNCTION switch\n";
			this->PositionDefinedByFunction = true;
			
			Initialize_ParticlePositions_byFunction();
			
		break;
		case LUA_TSTRING:
		
			cout << "LUA_TSTRING switch\n";
			if (strcasecmp(lua_tostring(this->L, 1), "distribution") == 0) {
			
				// TODO GEANT4 provides a distribution function.
				
			}
		
		break;
		case LUA_TNIL:
		
			cout << "Error. Nil value for Particles_Position\n";
		
		break;
		default:
		
		
		break;
		
	}
	
	// Pop Value and Particle_Table
	lua_pop(this->L, 2);
	
}

void ParticlesConfigLua::Parse_ParticleEnergy() {
	
	LoadTable("Particle_Table");
	lua_pushstring(this->L, "Energy");
	lua_gettable(this->L, -2);
	
	switch (lua_type(this->L, -1)) {
	
		// Two numbers, low and high. Uniform distribution
		case LUA_TTABLE: SetEnergyByRange(); break;
		
		// Allow the user to define their own distribution of energy
		case LUA_TFUNCTION: break;
		
		// All particles have the same energy
		case LUA_TNUMBER: SetEnergyByNumber(); break;
		
		// Did not provide energy value.
		case LUA_TNIL: break;
		
		default: break;
		
	}
	//Pops value and Particle_Table
	lua_pop(this->L, 2);
	
}
void ParticlesConfigLua::Parse_ParticleTypes() {
	
	LoadTable("Particle_Table");
	lua_pushstring(this->L, "Primary_Particles");
	lua_gettable(this->L, -2);
	
	switch (lua_type(this->L, -1)) {
	
		case LUA_TSTRING: SetPrimariesByString(); break;
		case LUA_TFUNCTION: SetPrimariesByFunction(); break;
		default: break;
		
	}
	
	//Pops value and Particle_Table
	lua_pop(this->L, 2);
	
}

void ParticlesConfigLua::Parse_ParticleMomentum() {
	
	LoadTable("Particle_Table");
	lua_pushstring(this->L, "Momentum_Direction");
	lua_gettable(this->L, -2);
	
	switch (lua_type(this->L, -1)) {
		
		case LUA_TTABLE:
		
			lua_pop(this->L, 1);
			SetMomentumByTable();
			lua_pushnil(this->L);
		
		break;
		case LUA_TFUNCTION: SetMomentumByFunction(); break;
		default: break;
		
	}
	
	//Pops value and Particle_Table
	lua_pop(this->L, 2);
	
}

void ParticlesConfigLua::SetEnergyByRange() {
	
	lua_pushinteger(this->L, 1);
	lua_gettable(this->L, -2);
	double E_Low = lua_tonumber(this->L, -1);
	lua_pop(this->L, 1);
	
	lua_pushinteger(this->L, 2);
	lua_gettable(this->L, -2);
	double E_High = lua_tonumber(this->L, -1);
	lua_pop(this->L, 1);
			
	cout << "Energy range = " << E_Low << ":" << E_High << "\n";
			
	for (int i = 0;i < this->NumberOfEvents;i++) {
			
		for (int j = 0;j < this->PrimariesPerEvent;j++) {
				
			this->FourVectors[i][j].E = E_Low + GetRandomDouble()*(E_High - E_Low);
			
		}
				
	}
	
}

void ParticlesConfigLua::SetEnergyByNumber() {

	double Energy = lua_tonumber(this->L, -1);
			
	for (int i = 0;i < this->NumberOfEvents;i++) {
			
		for (int j = 0;j < this->PrimariesPerEvent;j++) {
				
			this->FourVectors[i][j].E = Energy;
					
		}
				
	}
	
}

void ParticlesConfigLua::SetEnergyByFunction() {
	
	Load_Function();
	
	for (int i = 1;i <= this->NumberOfEvents;i++) {
	
		for (int j = 0; j < this->PrimariesPerEvent;j++) {
			
			lua_pushinteger(this->L, this->PrimariesPerEvent * (i-1) + 1 + j);
			lua_gettable(this->L, -2);
			
			this->FourVectors[i][j].E = lua_tonumber(this->L, -1);
			
			//pops value
			lua_pop(this->L, 1);
			
		}
		
	}
	//pops table
	lua_pop(this->L, 1);
	
}

void ParticlesConfigLua::SetPrimariesByString() {
	
	for (int i = 0;i < this->NumberOfEvents;i++) {
	
		for (int j = 0;j < this->PrimariesPerEvent;j++) {
		
			this->FourVectors[i][j].ParticleName = lua_tostring(this->L, -1);
			
		}
		
	}
	
}

void ParticlesConfigLua::SetPrimariesByFunction() {
	
	Load_Function();
	
	for (int i = 1; i <= this->NumberOfEvents;i++) {
	
		for (int j = 0;j < this->PrimariesPerEvent;j++) {
		
			lua_pushinteger(this->L, this->PrimariesPerEvent * (i-1) + 1 + j);
			lua_gettable(this->L, -2);
			
			this->FourVectors[i][j].ParticleName = lua_tostring(this->L, -1);
			
			// pops value
			lua_pop(this->L, 1);
			
		}
		
	}
	
}

void ParticlesConfigLua::SetMomentumByTable() {
	
	G4ThreeVector Momentum = GetG4ThreeVector("Momentum_Direction", 1.0);
	
	for (int i = 0;i < this->NumberOfEvents;i++) {
	
		for (int j = 0;j < this->PrimariesPerEvent;j++) {
		
			this->FourVectors[i][j].P_x = Momentum.x();
			this->FourVectors[i][j].P_y = Momentum.y();
			this->FourVectors[i][j].P_z = Momentum.z();
			
		}
		
	}
	
}
void ParticlesConfigLua::SetMomentumByFunction() {
	
	Load_Function();
	
	for (int i = 1; i <= this->NumberOfEvents;i++) {
	
		for (int j = 0;j < this->PrimariesPerEvent;j++) {
			
			G4double *Momenta[3] = {&this->FourVectors[i-1][j].P_x,
                                    &this->FourVectors[i-1][j].P_y,
                                    &this->FourVectors[i-1][j].P_z};
		
			lua_pushinteger(this->L, this->PrimariesPerEvent * (i-1) + 1 + j);
			lua_gettable(this->L, -2);
			
			for (int k = 1;k < 4;k++) {
			
				lua_pushinteger(this->L, k);
				lua_gettable(this->L, -2);
				
				*(Momenta[i-1]) = lua_tonumber(this->L, -1);
				//Pops value
				lua_pop(this->L, 1);
				
			}
			
			// pops value
			lua_pop(this->L, 1);
			
		}
		
	}
	
}

/*
 * ReadFile_FourVector()
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void ParticlesConfigLua::ReadFile_FourVector() {
	
	string path = this->Module_Path + "/" + this->ParticleFile;
	this->NumberOfEvents = DetermineNumberOfEvents(path);
	this->FourVectors = new vector<FourVector>[this->NumberOfEvents];
	
	FILE *fp = fopen(path.c_str(), "r");
	FourVector Temp_FourVector;
	int eventnum = 0;
	/*
	 * this->ParticleFileType has the following substrings:
	 * 
	 * 		"with name"
	 * 		"with position"
	 * 
	 * Reads a file with the following format:
	 * 
	 * <Particle Name> , <E/c, P_x, P_y, P_z> , <X, Y, Z>
	 *      Name       ,      Four Vector     ,  Position
	 * 
	 * */
	 
	if (this->FileHasParticleNames && this->FileHasPosition) {
	
		string input = "%d: %s %lf %lf %lf %lf %lf %lf %lf";
		char Temp_ParticleName[256] = {'\0'};
		while (fscanf(fp, input.c_str(), &eventnum, 
                                         Temp_ParticleName,
                                         &Temp_FourVector.E,
                                         &Temp_FourVector.P_x,
                                         &Temp_FourVector.P_y,
                                         &Temp_FourVector.P_z,
                                         &Temp_FourVector.X,
                                         &Temp_FourVector.Y,
                                         &Temp_FourVector.Z) != EOF) 
		{
			
			Temp_FourVector.ParticleName = G4String(Temp_ParticleName);
			this->FourVectors[eventnum].push_back(Temp_FourVector);
			
		}
		SetObjectVarsWithFileInformation();
	
	/*
	 * this->ParticleFileType has the following substrings:
	 * 
	 * 		"with name"
	 * 
	 * Reads a file with the following format:
	 * 
	 * <Particle Name> , <E/c, P_x, P_y, P_z>
	 *      Name       ,      Four Vector
	 * 
	 * */
	
	} else if (this->FileHasParticleNames) {
	
		string input = "%d: %s %lf %lf %lf %lf";
		char Temp_ParticleName[256] = {'\0'};
		
		//Temp_FourVector.X = this->Position.x();
		//Temp_FourVector.Y = this->Position.y();
		//Temp_FourVector.Z = this->Position.z();
		
		while (fscanf(fp, input.c_str(), &eventnum,
                                         Temp_ParticleName,
                                         &Temp_FourVector.E,
                                         &Temp_FourVector.P_x,
                                         &Temp_FourVector.P_y,
                                         &Temp_FourVector.P_z) != EOF) 
		{
			
			Temp_FourVector.ParticleName = G4String(Temp_ParticleName);
			this->FourVectors[eventnum].push_back(Temp_FourVector);
			
		}
		SetObjectVarsWithFileInformation();
		Parse_ParticlePosition();
		
	/*
	 * this->ParticleFileType has the following substrings:
	 * 
	 * 		"with position"
	 * 
	 * Reads a file with the following format:
	 * 
	 * <E/c, P_x, P_y, P_z> , <X, Y, Z>
	 *      Four Vector     , Position
	 *  
	 * */
	
	} else if (this->FileHasPosition) {
		
		string input = "%d: %lf %lf %lf %lf %lf %lf %lf";
		Temp_FourVector.ParticleName = this->PrimaryParticle_Name;
		
		while (fscanf(fp, input.c_str(), &eventnum,
                                         &Temp_FourVector.E,
                                         &Temp_FourVector.P_x,
                                         &Temp_FourVector.P_y,
                                         &Temp_FourVector.P_z,
                                         &Temp_FourVector.X,
                                         &Temp_FourVector.Y,
                                         &Temp_FourVector.Z) != EOF) 
		{
			
			
			this->FourVectors[eventnum].push_back(Temp_FourVector);
			
		}
		SetObjectVarsWithFileInformation();
		Parse_ParticleTypes();
		
	/*
	 * this->ParticleFileType has ***none*** the following substrings:
	 * 
	 * 		"with name"
	 * 		"with position"
	 * 
	 * 	Reads a file with the following format:	
	 * 
	 * <E/c, P_x, P_y, P_z>
	 *      Four Vector
	 * 
	 * */	
		
	} else {
		
		string input = "%d: %lf %lf %lf %lf";
		
		Temp_FourVector.ParticleName = this->PrimaryParticle_Name;
		while (fscanf(fp, input.c_str(), &eventnum,
                                         &Temp_FourVector.E,
                                         &Temp_FourVector.P_x,
                                         &Temp_FourVector.P_y,
                                         &Temp_FourVector.P_z) != EOF) 
		{
			
			this->FourVectors[eventnum].push_back(Temp_FourVector);
			
		}
		SetObjectVarsWithFileInformation();
		Parse_ParticlePosition();
		Parse_ParticleTypes();
		
	}
	
	fclose(fp);
	
}

void ParticlesConfigLua::SetObjectVarsWithFileInformation() {

	
	this->PrimariesPerEvent = (int)this->FourVectors[0].size();
	this->TotalNumberOfPrimaries = this->PrimariesPerEvent * this->NumberOfEvents;
	
	cout << "Number Of Events = " << this->NumberOfEvents << "\n";
	cout << "Primaries per Event = " << this->PrimariesPerEvent << "\n";
	
}

