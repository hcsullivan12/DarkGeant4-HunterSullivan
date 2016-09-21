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

struct DefaultConfigStruct {
	
	string modulename;
	string File;
	
	G4VUserPhysicsList *physicslist;
	
};

lua_State *InitializeLuaInterpreter(string file);
DefaultConfigStruct *ReadDefaultConfigFile(string ConfigDirectory);

#endif

