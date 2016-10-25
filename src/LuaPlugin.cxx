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
#include "Utilities.hh"

// C/C++ Headers
#include <cstring>

// Geant4 Headers
#include "QGSP_BERT.hh"


#define GetNumberFromGlobal_NoHalt(var, DefaultValue) \
                            GetGlobalVariable(var, LUA_TNUMBER, \
                            DefaultValue, &lua_tonumber_shim, false)
                            
#define GetNumberFromGlobal_WithHalt(var) \
                            GetGlobalVariable(var, LUA_TNUMBER, \
                            0.0, &lua_tonumber_shim, true)
                            
#define GetIntegerFromGlobal_NoHalt(var, DefaultValue) \
                            GetGlobalVariable(var, LUA_TNUMBER, \
                            DefaultValue, &lua_tointeger_shim, false)
                            
#define GetIntegerFromGlobal_WithHalt(var) \
                            GetGlobalVariable(var, LUA_TNUMBER, \
                            0, &lua_tointeger_shim, true)
                            
#define GetStringFromGlobal_NoHalt(var, DefaultValue) \
                            GetGlobalVariable(var, LUA_TNUMBER, \
                            DefaultValue, &lua_tostring_shim, false)
                            
#define GetStringFromGlobal_WithHalt(var) \
                            GetGlobalVariable(var, LUA_TNUMBER, \
                           "", &lua_tostring_shim, true)

/*
 * 
 * Useful Macro's that help increase code readibility by eliminating
 * a lot of boiler plate code when calling GetElementFromTable.
 * 
 * */
#define GetNumberFromTable_WithHalt(element, ErrorMessage) \
                            GetElementFromTable(element, \
                            ErrorMessage, 0.0, LUA_TNUMBER, \
                            &lua_tonumber_shim, true)
                            
#define GetNumberFromTable_NoHalt(element, ErrorMessage, DefaultValue) \
                            GetElementFromTable(element, \
                            ErrorMessage, DefaultValue, LUA_TNUMBER, \
                            &lua_tonumber_shim, false)
                            
#define GetIntegerFromTable_WithHalt(element, ErrorMessage) \
                            GetElementFromTable(element, \
                            ErrorMessage, 0, LUA_TNUMBER, \
                            &lua_tointeger_shim, true)
                            
#define GetIntegerFromTable_NoHalt(element, ErrorMessage) \
                            GetElementFromTable(element, \
                            ErrorMessage, 0, LUA_TNUMBER, \
                            &lua_tointeger_shim, false)
                            
#define GetStringFromTable_WithHalt(element, ErrorMessage) \
                            GetElementFromTable(element, \
                            ErrorMessage, "", LUA_TSTRING, \
                            &lua_tostring_shim, true)
                            
#define GetStringFromTable_NoHalt(element, ErrorMessage, DefaultValue) \
                            GetElementFromTable(element, \
                            ErrorMessage, DefaultValue, LUA_TSTRING, \
                            &lua_tostring_shim, false)

#define GetBooleanFromTable_NoHalt(element, ErrorMessage, DefaultValue) \
                            GetElementFromTable(element, \
                            ErrorMessage, 0, LUA_TBOOLEAN, \
                            &lua_toboolean_shim, false)


const char *lua_tostring_shim(lua_State *L, int index);
int lua_tointeger_shim(lua_State *L, int index);
double lua_tonumber_shim(lua_State *L, int index);


static const string DefaultConfigDirectory = "config";

/*
 * * Comment
 * 
 * Since lua_toxxxx is just are just macros, I can't easily use
 * function pointers to simplify the template function in LuaPlugin.hh
 * 
 * */
 
const char *lua_tostring_shim(lua_State *L, int index) {
		
	return lua_tostring(L, index);
	
}

int lua_tointeger_shim(lua_State *L, int index) {

	return lua_tointeger(L, index);
	
}

// Returns 0 if false/nil, 1 if true.
int lua_toboolean_shim(lua_State *L, int index) {
	
	return lua_toboolean(L, index);
	
}

double lua_tonumber_shim(lua_State *L, int index) {

	return lua_tonumber(L, index);
	
}









/*
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Class LuaInstance member functions
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

	lua_pop(this->L, -1);
	lua_close(this->L);
	this->L = NULL;
	
}

LuaInstance::~LuaInstance() {
	
	if (this->L != NULL) {
		
		lua_pop(this->L, -1);
		lua_close(this->L);
		
	}
	
}









/*
 * 
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 	Class ConfigLuaInstance member functions
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 * */
 
 
 
 
 
 
 
 
 
 
 
/*
 * ConfigLuaInstance::ConfigLuaInstance(string ModulePath)
 * 
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










/*
 * 
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 	Class DetectorConfigLuaInstance member functions
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 * */
 
 
 
 
 
 
 
 
 

/*
 * DetectorConfigLuaInstane::DetectorConfigLuaInstance(string ModulePath)
 * 
 * 
 * */

DetectorConfigLuaInstance::DetectorConfigLuaInstance(string ModulePath)
: LuaInstance(ModulePath + string("/DetectorConfig.lua"))
{
	LoadTable("World");
	Initialize_world();
	
	LoadTable("DetectorConfig");
	Initialize_number_of_detector_components();
	Initialize_detector_components();
	
}

/*
 * DetectorConfigLuaInstance::~DetectorConfigLuaInstance()
 * 
 * 
 * */

DetectorConfigLuaInstance::~DetectorConfigLuaInstance() 
{
		
	
}

void DetectorConfigLuaInstance::Initialize_world() {
	
	G4String Volume_Type = GetStringFromTable_WithHalt("Volume_Type",
                                  "No Volume_Type specified for world");
                              
    G4String Name = GetStringFromTable_NoHalt("World_Name",
                                              "Default World Name",
                                              "World");
    this->World = WithVolumeGetDetectorComponent(Volume_Type, Name);    
}

/*
 * DetectorConfigLuaInstance::Initialize_number_of_detector_components()
 * 
 * 
 * 
 * */

void DetectorConfigLuaInstance::Initialize_number_of_detector_components() {
	
	this->Number_of_Dectector_Components = GetNumberFromTable_WithHalt(
                                "Number_of_Detector_Components",
                                "Missing Number_of_Detector_Components"
                                + string(" in DetectorConfig table."));
	                            
	if (this->Number_of_Dectector_Components <= 0) {
	
		cout << "You did not define the variable ";
		cout << "Number_of_Detector_Components sufficiently.\n";
		cout << "Please be sure you set it to an integer greater than 0";
		cout << ".\n";
		cout << "Halting execution\n";
		exit(0);
		
	}
	
}



/*
 * DetectorConfigLuaInstance::Initialize_detector_components()
 * 
 * 
 * 
 * */

void DetectorConfigLuaInstance::Initialize_detector_components() {
	
	for (int i = 1; i <= this->Number_of_Dectector_Components;i++) {
	
		//Pop entire stack
		lua_pop(this->L, -1);
		
		string tempstring = ConvertIntToString(i);
		
		cout << "\nDetectorComponent_" + tempstring << ":\n";
		LoadTable("DetectorComponent_" + tempstring);
		
		G4String Volume_Type = GetStringFromTable_WithHalt("Volume_Type",
		                     "You didn't define an appropriate volume "
		                     + string("for DetectorComponent_"
		                     + tempstring));
        G4String Name = GetStringFromTable_NoHalt("Component_Name",
                                          "Default Component_Name Used",
                             "DetectorComponent_" + tempstring);            
       /*
        * * Comment
        * 
        * 		Since I've passed true for Halt Execution, I'm going to
        * 		assume that the value that Volume_Type is valid.
        * 
        * */
		this->Components.push_back(WithVolumeGetDetectorComponent(Volume_Type, Name));
		
	}
	cout << "\n";
	
}


DetectorComponent *DetectorConfigLuaInstance::WithVolumeGetDetectorComponent(G4String Volume_Type, G4String Name) {
	
	DetectorComponent *Component;
	if (Volume_Type == "Cylinder")
		Component = MakeDetectorComponent_Cylinder(Name);
    else if (Volume_Type == "Box")
		Component = MakeDetectorComponent_Box(Name);
	
	return Component;
	
}


/*
 * DetectorConfigLuaInstance::MakeDetectorComponent_Cylinder()
 * 
 * 
 * 
 * 
 * */
 
DetectorComponent_Cylinder *DetectorConfigLuaInstance::MakeDetectorComponent_Cylinder(G4String Name) {
	
	
	G4String MaterialString = GetStringFromTable_WithHalt("Material",
                                        "No Material found."
                                        + string(" Halting Execution"));
	     
	                                      
	G4double Inner_Radius = GetNumberFromTable_NoHalt("Inner_Radius",
                                             "No Inner_Radius found."
                                             + string(" Set to 0.0"),
                                             0.0);
                                                                               
	G4double Outer_Radius = GetNumberFromTable_WithHalt("Outer_Radius",
                                             "No Outer_Radiys found."
                                        + string(" Halting Execution"));
                                      
	G4double Start_Angle = GetNumberFromTable_NoHalt("Start_Angle",
                                             "No Start_Angle found."
                                             + string(" Set to 0.0"),
                                             0.0);
                                               
	G4double End_Angle = GetNumberFromTable_NoHalt("End_Angle",
                                             "No End_Angle found."
                                             + string(" Set to 360."),
                                             360.);
                                            
	G4double Half_Length = GetNumberFromTable_WithHalt("Half_Length",
                                             "No Half_Length found."
                                        + string(" Halting Execution"));
                                        
	G4String Inside = GetStringFromTable_WithHalt("Inside",
                                                 "Please define Inside."
                                        + string(" Halting Execution"));
                                         
                                         
	G4ThreeVector Position = MakePositionG4ThreeVector();
   
   
	return new DetectorComponent_Cylinder(Name,
                                      Inner_Radius,
                                      Outer_Radius,
                                      Start_Angle,
                                      End_Angle,
                                      Half_Length,
                                      Position,
                                      MaterialString,
                                      Inside);
   
}




/*
 * DetectorConfigLuaInstance::MakeDectorComponent_Box()
 * 
 * 
 * 
 * */

DetectorComponent_Box *DetectorConfigLuaInstance::MakeDetectorComponent_Box(G4String Name) {
    
	G4double X = GetNumberFromTable_WithHalt("X", "Did not provide X "+
                                    string("value. Halting Execution"));
	
	G4double Y = GetNumberFromTable_WithHalt("Y", "Did not provide Y "+
                                    string("value. Halting Execution"));
                                     
	G4double Z = GetNumberFromTable_WithHalt("Z", "Did not provide Z "+
                                    string("value. Halting Execution"));
                                    
	G4String Inside = GetStringFromTable_WithHalt("Inside",
                                        "Please define Inside."
                                        + string(" Halting Execution"));
                                     
                                     
	G4String MaterialString = GetStringFromTable_WithHalt("Material",
                               "Did not provide a valid material");
                                     
	G4ThreeVector Position = MakePositionG4ThreeVector();
	
	return new DetectorComponent_Box(Name, X, Y, Z, 
                                     Position, MaterialString, Inside);
                                     
}




/*
 * DetectorConfigLuaInstance::MakePositionG4ThreeVector()
 * 
 * 
 * 
 * */

G4ThreeVector DetectorConfigLuaInstance::MakePositionG4ThreeVector() {

	lua_pushstring(this->L, "Position");
	lua_gettable(this->L, -2);
	
	if (lua_type(this->L, -1) != LUA_TTABLE) {
		
		cout << "Something went wrong with DetectorComponent.Position\n";
		throw;
		
	}
	
	G4double PositionArray[3] = {0.0, 0.0, 0.0};
	for (int i = 1;i < 4;i++) {
		lua_pushinteger(this->L, i);
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
	
	return G4ThreeVector(PositionArray[0] * m, 
                         PositionArray[1] * m, 
                         PositionArray[2] * m);
}









/*
 * 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * class MaterialConfigLua member functions
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 * */






MaterialConfigLua::MaterialConfigLua(string ModulePath)
 : LuaInstance(ModulePath + string("/Materials.lua")) 
{
	
	Initialize_NumberOfMaterials();
	Initialize_MaterialsVector();
	
}

MaterialConfigLua::~MaterialConfigLua() {
	
	
	
}

void MaterialConfigLua::Initialize_NumberOfMaterials() {
	
	this->NumberOfMaterials = GetIntegerFromGlobal_WithHalt(
	                                             "Number_Of_Materials");
	
	
}

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

Material *MaterialConfigLua::ConstructMaterial_ByDatabase() {

	G4String DatabaseName = GetStringFromTable_WithHalt("G4Name",
                                "Make sure you have a G4Name variable!"
                                + string(" Halting Execution.\n"));
	
	return new Material(DatabaseName);
	
}



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
	
	return new Material(Name, NumberOfProtons, AtomicMass * g/mole, Density * g/cm3);
	
}
