/*
 * ConfigLuaInstance.cxx
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


#include "ConfigLuaInstance.hh"

// User Headers
#include "PhysicsList.hh"

// Geant4 Headers
#include "QGSP_BERT.hh"
 
 
/*
 * ConfigLuaInstance::ConfigLuaInstance(string ModulePath)
 * 
 * 
 * 
 * */

ConfigLuaInstance::ConfigLuaInstance(string ModulePath) 
: LuaInstance(ModulePath, "Config.lua")
{
	
	LoadTable("ConfigTable");
	Initialize_modulename();
	Initialize_physicslist();
	lua_pop(this->L, 1);
	
	LoadTable("DarkGeantOutputFile");
	Initialize_DarkGeantOutputFile();
	Initialize_DarkGeantOutputLocation();
	lua_pop(this->L, 1);
	
}

/*
 * ConfigLuaInstance::~ConfigLuaInstance()
 * 
 * 
 * */

ConfigLuaInstance::~ConfigLuaInstance()
{
	
	
}

/*
 * ConfigLuaInstance::Initialize_modulename()
 * 
 * 
 * */

void ConfigLuaInstance::Initialize_modulename() {
	
	this->modulename = GetStringFromTable_NoHalt("Module_Name",
                                             "No Module_Name set",
                                             "Default Module_Name set");

}

/*
 * ConfigLuaInstance::Initialize_physicslist()
 * 
 * 
 * TODO
 * 
 * 		Add other physics lists
 * 
 * */
void ConfigLuaInstance::Initialize_physicslist() {
	
	string PhysicsListString = GetStringFromTable_NoHalt("PhysicsList",
                                                   "No PhysicsList set",
                                                   "Default");
	
	if (PhysicsListString == "Default")
		this->physicslist = new PhysicsList();
	else if (PhysicsListString == "QGSP_BERT")
		this->physicslist = new QGSP_BERT();
	
}

void ConfigLuaInstance::Initialize_DarkGeantOutputFile() {
	
	this->DarkGeantOutputFile = GetStringFromTable_NoHalt("Name",
                                            "Using default output name",
                                            "DarkGeant4Output.dat");
	
}

void ConfigLuaInstance::Initialize_DarkGeantOutputLocation() {
	
	this->DarkGeantOutputLocation = GetStringFromTable_NoHalt("Location",
                     "No output location specified. Using default path",
                     this->Module_Path);
	
}



