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
int lua_tointeger_shim(lua_State *L, int index);


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

int lua_tointeger_shim(lua_State *L, int index) {

	return lua_tointeger(L, index);
	
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
		cout << lua_tostring(this->L, -1) << "\n";
		throw;
		
	}
	
	
	
}

void LuaInstance::PopLuaStack(int StackIndex = -1) {

	lua_pop(this->L, StackIndex);
	
}

void LuaInstance::LoadTable(string table) {

	lua_getglobal(this->L, table.c_str());
	
	if (!lua_istable(this->L, -1)) {
	
		cout << "Table " << table << " does not exist\n";
		throw;
		
	}
	
}

/*
 * 
 * CloseLuaState()
 * 
 * * Comment
 * 	
 * 		This function is practically identical to the class destructor
 * 		in function. So why then implement it? Suppose you want the 
 * 		object to stay in memory to access it's member functions 
 * 		but you no longer need the lua instance. This function
 * 		grants that ability.
 *  
 * */
void LuaInstance::CloseLuaState() {

	PopLuaStack();
	lua_close(this->L);
	
}

LuaInstance::~LuaInstance() {
	
	if (this->L != NULL) {
		
		PopLuaStack();
		lua_close(this->L);
		
	}
	
}



/*
 * 
 * 
 * 	Class ConfigLuaInstance member functions
 * 
 * 
 * */
 
ConfigLuaInstance::ConfigLuaInstance(string ModulePath) 
: LuaInstance(ModulePath + string("/Config.lua"))
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
   cout << "Module name = " << this->modulename;
	
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
	
	cout << "Physics list is " << PhysicsListString << "\n";
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

DetectorConfigLuaInstance::DetectorConfigLuaInstance(string ModulePath)
: LuaInstance(ModulePath + string("/DetectorConfig.lua"))
{
	
	LoadTable("DetectorConfig");
	
	Initialize_number_of_detector_components();
	
}

DetectorConfigLuaInstance::~DetectorConfigLuaInstance() 
{
		
	
}

void DetectorConfigLuaInstance::Initialize_number_of_detector_components() {
	
	this->Number_of_Dectector_Components = GetElementFromTable(
	                            "Number_of_Detector_Components",
	                            "Missing Number_of_Detector_Components",
	                            0,
	                            LUA_TNUMBER,
	                            &lua_tointeger_shim);
	                            
	if (this->Number_of_Dectector_Components <= 0) {
	
		cout << "You did not define the variable ";
		cout << "Number_of_Detector_Components.\n";
		cout << "Please be sure you set it to an integer.\n";
		
		cout << "Halting execution\n";
		exit(0);
		
	}
	
}
