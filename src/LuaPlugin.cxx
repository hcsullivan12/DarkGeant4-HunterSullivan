/*
 * LuaPlugin.cxx
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

#include "LuaPlugin.hh"

// User Headers
#include "PhysicsList.hh"

// Geant4 Headers
#include "QGSP_BERT.hh"

const char *lua_tostring_shim(lua_State *L, int index);


static const string DefaultConfigDirectory = "config";

/*
 * Since lua_tostring is just a macro of lua_tolstring and because
 * I initially intended to use function pointers for the various
 * lua_toxxx functions, I had to create this shim around the macro.
 * 
 * */
const char *lua_tostring_shim(lua_State *L, int index) {
		
	return lua_tostring(L, index);
	
}


/*
 * 
 * Class LuaInstance member functions
 * 
 * * Comment
 * 
 * 		Later on it might be useful to load one of the default
 * 		files, or have a parameter in one of the scripts to point
 * 		to a default file.
 * 
 * 		For now I'll just throw an unhandled exception.
 * 
 * */

LuaInstance::LuaInstance(string FilePath) {

	this->L = luaL_newstate();
	luaL_openlibs(L);
	
	if (luaL_loadfile(L, FilePath.c_str()) || lua_pcall(L, 0, 0, 0)) {
		
		cout << "Cannot run " << FilePath << "\n";
		throw;
		
	}
	
	
	
}

void LuaInstance::PopLuaStack(int StackIndex = 1) {

	lua_pop(this->L, StackIndex);
	
}

void LuaInstance::LoadTable(string table) {

	lua_getglobal(this->L, table.c_str());
	
	if (!lua_istable(this->L, -1)) {
	
		cout << "Table " << table << " does not exist\n";
		throw;
		
	}
	
}

LuaInstance::~LuaInstance() {
	
	PopLuaStack();
	lua_close(this->L);
	
}



/*
 * 
 * 
 * 	Class ConfigLuaInstance member functions
 * 
 * 
 * */
 
ConfigLuaInstance::ConfigLuaInstance(string FilePath) 
: LuaInstance(FilePath)
{
	
	LoadTable("ConfigTable");
	Initialize_modulename();
	Initialize_physicslist();
	
}
ConfigLuaInstance::~ConfigLuaInstance()
{
	
	
}

void ConfigLuaInstance::Initialize_modulename() {
	
	this->modulename = GetElementFromTable("Module_Name",
                                     "No Module_Name set",
                                     "Default Module Name",
                                     LUA_TSTRING,
                                     &lua_tostring_shim);
   PopLuaStack(ONE);
	
}

/*
 * 
 * TODO
 * 
 * Add other physics lists
 * 
 * */
void ConfigLuaInstance::Initialize_physicslist() {
	
	string PhysicsListString = GetElementFromTable("PhysicsList",
                                                   "No PhysicsList set",
                                                   "Default set",
                                                   LUA_TSTRING,
                                                   &lua_tostring_shim);
                                            
	PopLuaStack(ONE);
	
	if (PhysicsListString == "Default")
		this->physicslist = new PhysicsList();
	else if (PhysicsListString == "QGSP_BERT")
		this->physicslist = new QGSP_BERT();
	
}


/*
 * 
 * 
 * 	Class DetectorConfigLuaInstance member functions
 * 
 * 
 * */

DetectorConfigLuaInstance::DetectorConfigLuaInstance(string FilePath)
: LuaInstance(FilePath)
{
	
	
}

DetectorConfigLuaInstance::~DetectorConfigLuaInstance() 
{
		
	
}
