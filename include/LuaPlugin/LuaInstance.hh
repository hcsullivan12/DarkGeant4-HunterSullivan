/*
 * LuaInstance.hh
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


#ifndef LUAINSTANCE_HH
#define LUAINSTANCE_HH

// Third Party Headers
#include "lua.hpp"

// C/C++ Headers
#include <iostream>
#include <string>
#include <exception>
#include <vector>

// Geant 4 Headers
#include "G4ThreeVector.hh"

using std::cout;
using std::string;
using std::vector;

class LuaInstance {
	
	/*
	 * 
	 * Class member variables
	 * 
	 * */
	protected:
	
		lua_State *L;
		
		string Module_Path;
		string File;
		string File_Total_Path;
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		LuaInstance(string Module_Path, string File);
		~LuaInstance();
		
		void CloseLuaState();
		
	protected:
	
	
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
		void LoadTable(string table);
		
		template<typename T, typename U>
		T GetGlobalVariable(string var,
		                    int VAR_TYPE,
		                    T DefaultValue,
                            U (*lua_Function)(lua_State *L, int index),
                            bool HaltExecution)
        {
			
			lua_getglobal(this->L, var.c_str());
			
			if (lua_type(this->L, -1) != VAR_TYPE) {
				
				cout << var << " wrong type\n";
				lua_pop(this->L, 1);
				if (HaltExecution) {
					
					cout << "Halting execution";
					exit(0);
					
				}
				return DefaultValue;
				
			}
			T ReturnValue = lua_Function(this->L, -1);
			lua_pop(this->L, 1);
			return ReturnValue;
			
		}
			
		template<typename T, typename U>
		T GetElementFromTable(string element, 
                              string ErrorMessage,
                              T DefaultValue,
                              int VAR_TYPE,
                              U (*lua_Function)(lua_State *L, int index),
                              bool HaltExecution)
                              
        {
			
			lua_pushstring(this->L, element.c_str());
			lua_gettable(this->L, -2);
	
			if (lua_type(this->L, -1) != VAR_TYPE) {
		
				cout << ErrorMessage << "\n";
				
				lua_pop(this->L, 1);
				if (HaltExecution == true)
					exit(0);
					
				return DefaultValue;
		
			}
			T ReturnValue = lua_Function(this->L, -1);
			lua_pop(this->L, 1);
			cout << element << " = " << ReturnValue << "\n";
			return ReturnValue;
			
		}
		G4ThreeVector GetG4ThreeVector(string TableName);
	
};


#endif

