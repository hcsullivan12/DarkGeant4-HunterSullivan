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

void ModuleName_Config (lua_State *L, ConfigTableStruct *Config);
void PhysicsList_Config(lua_State *L, ConfigTableStruct *Config);

static const int NumConfigFunctions = 2;
void (*ConfigFunctions[NumConfigFunctions])(lua_State *L, ConfigTableStruct *Config) = 
{   
	&ModuleName_Config,
	&PhysicsList_Config
};

static const string DefaultConfigDirectory = "config";


/*
 * Initializes Lua interpreter with zero stack elements.
 * 
 * */
lua_State *InitializeLuaInterpreter(string file) {

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaL_loadfile(L, file.c_str());
	lua_pcall(L, 0, 0, 0);
	
	return L;
	
}

ConfigTableStruct *ReadDefaultConfigFile(string ConfigDirectory) {
	
	string ConfigFile = ConfigDirectory + "/config.lua";
	
	lua_State *L = InitializeLuaInterpreter(ConfigFile);
	
	ConfigTableStruct *ThisConfigTableStruct = new ConfigTableStruct;
	
	/*
	 * Loads ConfigTable and checks to see that it's an appropriate 
	 * structure.
	 * 
	 * */
	lua_getglobal(L, "ConfigTable");
	if (!lua_istable(L,-1)) {
	
		cout << "ConfigTable is not a table!\n";
		throw;
		
	}
	for (int i = 0;i < NumConfigFunctions;i++)
		ConfigFunctions[i](L, ThisConfigTableStruct);
	lua_pop(L, 1);
	
	lua_close(L);
	return ThisConfigTableStruct;
	
}


/*
 * 
 * Assumes that the table is at the top of the stack prior to
 * calling this function
 * 
 * */
void SetStringPointerFromPreopenedTable(lua_State *L, 
                                        string element,
                                        string *pointer,
                                        string ErrorMessage,
                                        string DefaultValue)
{

	lua_pushstring(L, element.c_str());
	lua_gettable(L, -2);
	if (lua_type(L, -1) != LUA_TSTRING) {
	
		cout << ErrorMessage;
		*pointer = DefaultValue;
		
	} else {
	
		*pointer = lua_tostring(L, -1);
		
	}
	lua_pop(L, -1);
	
}


void ModuleName_Config (lua_State *L, ConfigTableStruct *Config) {
	
	SetStringPointerFromPreopenedTable(L,
                                       "ModuleName",
                                       &Config->modulename,
                                       "Error with ModuleName parameter\n",
                                       "Error_with_ModuleName");
	
	cout << "Module name set to = " << Config->modulename << "\n";
}

/*
 * Gets the value of ConfigTable.PhysicsList
 * 
 * */
void PhysicsList_Config(lua_State *L, ConfigTableStruct *Config) {
	
	string physicslist;
	
	SetStringPointerFromPreopenedTable(L,
                                       "PhysicsList",
                                       &physicslist,
                                       string("Error with PhysicsList")
                                       + string("parameter\nUsing")
                                       + string("default value\n"),
                                       "Default");
	
	
	if (physicslist == "Default")
		Config->physicslist = new PhysicsList();
	else if (physicslist == "QGSP_BERT")
		Config->physicslist = new QGSP_BERT();
	
	cout << physicslist << " Physics List loaded\n";
	
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
	
	
	
}
ConfigLuaInstance::~ConfigLuaInstance()
{
	
	
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
