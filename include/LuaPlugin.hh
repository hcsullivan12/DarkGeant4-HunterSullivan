/*
 * LuaPlugin.hh
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

#ifndef LUAPLUGIN_H
#define LUAPLUGIN_H

// Third Party Headers
#include "lua.hpp"

// C/C++ Headers
#include <iostream>
#include <string>
#include <exception>

// Geant 4 Headers
#include "G4VUserPhysicsList.hh"

using std::cout;
using std::string;

enum FileType {
	
	FOURVECTOR = 0,
	PLACEHOLDER
	
};

struct ConfigTableStruct {
	
	string modulename;
	G4VUserPhysicsList *physicslist;
	
};

struct FileTableStruct {
	
	string File;
	FileType Type;
	
};

lua_State *InitializeLuaInterpreter(string file);

void SetStringPointerFromPreopenedTable(lua_State *L, 
                                        string element,
                                        string *pointer,
                                        string ErrorMessage,
                                        string DefaultValue);

ConfigTableStruct *ReadDefaultConfigFile(string ConfigDirectory);


class LuaInstance {
	
	/*
	 * 
	 * Class member variables
	 * 
	 * */
	protected:
	
		lua_State *L;
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		LuaInstance(string FilePath);
		~LuaInstance();
		
	protected:
	
		void PopLuaStack(int StackIndex);
		void LoadTable(string table);
			
		/*
		* 
		* Functions include
		* 
		* lua_toboolean
		* lua_tolstring or lua_tostring (Read in the lua docs)
		* lua_tonumber
		* lua_tointeger
		* lua_tounsigned
		* 
		* Types include
		* 
		* LUA_TBOOLEAN
		* LUA_TNUMBER
		* LUA_TSTRING
		* 
		* */
		template<typename T, typename U>
		T GetElementFromTable(string element, 
                              string ErrorMessage,
                              T DefaultValue,
                              int VAR_TYPE,
                              U (*lua_Function)(lua_State *L, int index))
                              
        {
			
			lua_pushstring(this->L, element.c_str());
			lua_gettable(this->L, -2);
	
			if (lua_type(this->L, -1) != VAR_TYPE) {
		
				cout << ErrorMessage;
				return DefaultValue;
		
			}
			return lua_Function(this->L, -1);
			
		}
	
};

class ConfigLuaInstance : public LuaInstance {
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		ConfigLuaInstance(string FilePath);
		~ConfigLuaInstance();
	
	/*
	 * 
	 * TODO
	 * 
	 * Finish class
	 * 
	 * */
	
};

class DetectorConfigLuaInstance : public LuaInstance {
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		DetectorConfigLuaInstance(string FilePath);
		~DetectorConfigLuaInstance();
	
	/*
	 * 
	 * TODO
	 * 
	 * Finish class
	 * 
	 * */
	
};

#endif

