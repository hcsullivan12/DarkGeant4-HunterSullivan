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

// C/C++ Headers
#include <cstring>

// Geant4 Headers
#include "QGSP_BERT.hh"

const char *lua_tostring_shim(lua_State *L, int index);
int lua_tointeger_shim(lua_State *L, int index);
double lua_tonumber_shim(lua_State *L, int index);


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

double lua_tonumber_shim(lua_State *L, int index) {

	return lua_tonumber(L, index);
	
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
                                     &lua_tostring_shim,
                                     false);
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
                                                   "Default",
                                                   LUA_TSTRING,
                                                   &lua_tostring_shim,
                                                   false);
                                            
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
	Initialize_detector_components();
	
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
	                            &lua_tointeger_shim,
	                            true);
	                            
	if (this->Number_of_Dectector_Components <= 0) {
	
		cout << "You did not define the variable ";
		cout << "Number_of_Detector_Components.\n";
		cout << "Please be sure you set it to an integer.\n";
		
		cout << "Halting execution\n";
		exit(0);
		
	}
	PopLuaStack(1);
	
}

void DetectorConfigLuaInstance::Initialize_detector_components() {
	
	for (int i = 1; i <= this->Number_of_Dectector_Components;i++) {
	
		//Pop entire stack
		PopLuaStack(ALL);
		
		char tempstring[126] = {'\0'};
		sprintf(tempstring, "%d", i);
		
		LoadTable("DetectorComponent_" + string(tempstring));
		
		string Volume_Type = GetElementFromTable("Volume_Type",
                             "You didn't define a detector type for " 
                             + string(" DetectorComponent") 
                             + string(tempstring),
                             "Nothing",
                             LUA_TSTRING,
                             &lua_tostring_shim,
                             true);
                             
        PopLuaStack(ONE);
       /*
        * * Comment
        * 
        * 		Since I've passed true for Halt Execution, I'm going to
        * 		assume that the value that Volume_Type is valid.
        * 
        * */
        
        if (Volume_Type == "Cylinder")
			MakeDetectorComponent_Cylinder();
		else if (Volume_Type == "Box")
			MakeDetectorComponent_Box();
		
	}
	
}


/*
 * 
 * TODO
 * 
 * 		This function requires a refactoring. Also it would be
 * 		nice if the errors included the DetectorComponent_x number.
 * 
 * 
 * */
void DetectorConfigLuaInstance::MakeDetectorComponent_Cylinder() {
	
	G4double Inner_Radius = GetElementFromTable("Inner_Radius",
                                               "No Inner_Radius found."
                                               + string(" Set to 0.0"),
                                               0.0,
                                               LUA_TNUMBER,
                                               &lua_tonumber_shim,
                                               false);
                                               
    PopLuaStack(ONE);
	G4double Outer_Radius = GetElementFromTable("Outer_Radius",
                                         "No Outer_Radius found."
                                         + string(" Halting execution"),
                                         0.0,
                                         LUA_TNUMBER,
                                         &lua_tonumber_shim,
                                         true);
       
    PopLuaStack(ONE);                                  
    G4double Start_Angle = GetElementFromTable("Start_Angle",
                                               "No Start_Angle found."
                                               + string(" Set to 0.0"),
                                               0.0,
                                               LUA_TNUMBER,
                                               &lua_tonumber_shim,
                                               false);
                                               
   PopLuaStack(ONE);
   G4double End_Angle = GetElementFromTable("End_Angle",
                                            "No End_Angle found."
                                            + string(" Set to 360."),
                                            360.,
                                            LUA_TNUMBER,
                                            &lua_tonumber_shim,
                                            false);
                                            
   PopLuaStack(ONE);
   G4double Half_Length = GetElementFromTable("Half_Length",
                                         "No Half_Length found."
                                         + string(" Halting exectution"),
                                         0.0,
                                         LUA_TNUMBER,
                                         &lua_tonumber_shim,
                                         true);
                                         
    PopLuaStack(ONE);
    G4String MaterialString = GetElementFromTable("Material",
                                         "No Material found."
                                         + string(" Halting execution"),
                                         "",
                                         LUA_TSTRING,
                                         &lua_tostring_shim,
                                         true);
                                         
	PopLuaStack(ONE);
	G4ThreeVector Position = MakePositionG4ThreeVector();
   
   CylinderComponents.push_back(DetectorComponent_Cylinder(
                                Inner_Radius,
                                Outer_Radius,
                                Start_Angle,
                                End_Angle,
                                Half_Length,
                                Position,
                                MaterialString));
   
}
G4ThreeVector DetectorConfigLuaInstance::MakePositionG4ThreeVector() {

	lua_pushstring(this->L, "Position");
	lua_gettable(this->L, -2);
	
	if (lua_type(this->L, -1) != LUA_TTABLE) {
		
		cout << "Something went wrong";
		throw;
		
	}
	
	G4double PositionArray[3];
	for (int i = 1;i <= 3;i++) {
		lua_pushnumber(this->L, 1);
		lua_gettable(this->L, -2);
		if (lua_type(this->L, -1) != LUA_TNUMBER) {
	
			cout << "The elements of DetectorComponent.Position should"
			+ string("be a number!\n");
			throw;
		
		}
		PositionArray[i-1] = lua_tonumber(this->L, -1);
		// Pops number
		lua_pop(this->L, 1);
	}
	// Pops second table.
	lua_pop(this->L, 1);
	
	return G4ThreeVector(PositionArray[0], 
                         PositionArray[1], 
                         PositionArray[2]);
}

void DetectorConfigLuaInstance::MakeDetectorComponent_Box() {
	
	
	
}
