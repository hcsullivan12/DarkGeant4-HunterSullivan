/*
 * LuaInstance.cxx
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
 
#include "LuaInstance.hh"

#include "G4SystemOfUnits.hh"

using std::exception;

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


LuaInstance::LuaInstance(string Module_Path, string File) {

	this->Module_Path = Module_Path;
	this->File = File;
	this->File_Total_Path = Module_Path + string("/") + File;

	this->L = luaL_newstate();
	luaL_openlibs(L);
	
	if (luaL_loadfile(L, this->File_Total_Path.c_str()) || lua_pcall(L, 0, 0, 0)) {
		
		cout << "Cannot run " << this->File_Total_Path << "\n";
		cout << lua_tostring(this->L, -1) << "\n";
		throw;
		
	}
	
	
	
}

/*
 * LoadTable(string table)
 * 
 * * Description
 * 
 * 		...
 * 
 * */

void LuaInstance::LoadTable(string table) {

	lua_getglobal(this->L, table.c_str());
	
	if (!lua_istable(this->L, -1)) {
	
		cout << "Table " << table << " does not exist\n";
		throw;
		
	}
	
}

void LuaInstance::LoadTable_WithinTable(string table) {

	lua_pushstring(this->L, table.c_str());
	lua_gettable(this->L, -2);
	
	if (!lua_istable(this->L, -1)) {
	
		cout << "Table " << table << " does not exist\n";
		throw;
		
	}
	
}

/*
 * GetG4ThreeVector(string TableName)
 * 
 * * Description
 * 
 * 		...
 * 
 * */

G4ThreeVector LuaInstance::GetG4ThreeVector(string TableName) {

	/*
	 * Gets an element from a preloaded Table such that the equivalent
	 * C/C++ code would look something like this:
	 * 
	 * Table[TableName.c_str()]
	 * 
	 * */
	
	lua_pushstring(this->L, TableName.c_str());
	lua_gettable(this->L, -2);
	
	/*
	 * If the element received is not a table, then throw an exception
	 * which is typically unhandled.
	 * 
	 * */
	 
	if (lua_type(this->L, -1) != LUA_TTABLE) {
		
		cout << "Is " << TableName << " a table?\n";
		throw string("Not a table!");
		
	}
	
	/*
	 * The following code assumes that the table received in the
	 * previous code is a 1x3 array.
	 * 
	 * It reads the elements of the lua table and sets them to the
	 * elements of the PositionArray G4double array.
	 * 
	 * */
	
	G4double PositionArray[3] = {0.0, 0.0, 0.0};
	for (int i = 1;i < 4;i++) {
		
		// Gets element i from the table loaded.
		lua_pushinteger(this->L, i);
		lua_gettable(this->L, -2);
		
		/*
		 * If the element i is not a number, throw an exception. The
		 * exception is typically not handled to facilitate user
		 * correction.
		 * 
		 * */
		if (lua_type(this->L, -1) != LUA_TNUMBER) {
	
			cout << "The elements of " << TableName << "should be ";
			cout << "numbers!\n"; 
			throw;
		
		}
		/*
		 * So if the element is a number, get it and set
		 * PositionArray[i-1] to it.
		 * 
		 * Remember lua tables begin with 1, instead of 0 which is
		 * why we have the offset i-1.
		 * */
		
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
 * CloseLuaState()
 * 
 * * Comment
 * 	
 * 		This function is practically identical to the class destructor.
 * 		So why implement it then? Suppose you want the 
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

bool LuaInstance::IsGlobalNil(string var) {
	
	lua_getglobal(this->L, var.c_str());
	bool nil = IsNil();
	lua_pop(this->L, 1);
	
	return nil;
	
}

bool LuaInstance::IsTableElementNil(string var) {
	
	lua_pushstring(this->L, var.c_str());
	lua_gettable(this->L, -2);
	
	bool nil = IsNil();
	lua_pop(this->L, 1);
	
	return nil;
	
}

bool LuaInstance::IsNil() {

	return lua_type(this->L, -1) == LUA_TNIL;
	
}

LuaInstance::~LuaInstance() {
	
	if (this->L != NULL) {
		
		lua_pop(this->L, -1);
		lua_close(this->L);
		
	}
	
}

