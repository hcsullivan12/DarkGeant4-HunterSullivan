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
                            GetGlobalVariable(var, LUA_TSTRING, \
                            DefaultValue, &lua_tostring_shim, false)
                            
#define GetStringFromGlobal_WithHalt(var) \
                            GetGlobalVariable(var, LUA_TSTRING, \
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
                            
#define GetIntegerFromTable_NoHalt(element, ErrorMessage, DefaultValue) \
                            GetElementFromTable(element, \
                            ErrorMessage, DefaultValue, LUA_TNUMBER, \
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
                            
                            
int lua_tointeger_shim(lua_State *L, int index);
int lua_toboolean_shim(lua_State *L, int index);
double lua_tonumber_shim(lua_State *L, int index);
const char *lua_tostring_shim(lua_State *L, int index);


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
		void LoadTable_WithinTable(string table);
		
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
		
		bool IsGlobalNil(string var);
		bool IsTableElementNil(string var);
		G4ThreeVector GetG4ThreeVector(string TableName, double units);
	
	private:
	
		bool IsNil();
	
};


#endif

