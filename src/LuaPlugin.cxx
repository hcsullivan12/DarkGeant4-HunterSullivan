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

void PhysicsList_Config(lua_State *L, DefaultConfigStruct *Config);

static const int NumConfigFunctions = 1;
void (*ConfigFunctions[NumConfigFunctions])(lua_State *L, DefaultConfigStruct *Config) = 
{&PhysicsList_Config};

static const string DefaultConfigDirectory = "config";

DefaultConfigStruct *ReadDefaultConfigFile(string ConfigDirectory) {
	
	
	string ConfigFile = ConfigDirectory + "/config.lua";
	/*
	 * Loads state. Need to do a check here.
	 * 
	 * */
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaL_loadfile(L,  ConfigFile.c_str());
	lua_pcall(L, 0, 0, 0);
	
	DefaultConfigStruct *ThisDefaultConfigStruct = new DefaultConfigStruct;
	
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
		ConfigFunctions[i](L, ThisDefaultConfigStruct);
	
	lua_close(L);
	return ThisDefaultConfigStruct;
	
}


/*
 * Gets the value of ConfigTable.PhysicsList
 * 
 * */
void PhysicsList_Config(lua_State *L, DefaultConfigStruct *Config) {
	
	string physicslist;
	lua_pushstring(L, "PhysicsList");
	lua_gettable(L, -2);
	if (lua_type(L,-1) != LUA_TSTRING) {
		
		cout << "Error with PhysicsList parameter\n";
		cout << "Using default value\n";
		physicslist = "Default";
		
	}
	physicslist = lua_tostring(L, -1);
	
	/*
	 * Determine appropriate physics list from string.
	 * 
	 * */
	
}
