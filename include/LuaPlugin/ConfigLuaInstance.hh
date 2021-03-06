/*
 * ConfigLuaInstance.hh
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

#ifndef CONFIGLUAINSTANCE_HH
#define CONFICLUAINSTANCE_HH

// Third Party Headers
#include "lua.hpp"

// C/C++ Headers
#include <iostream>
#include <string>
#include <exception>
#include <vector>

// Geant 4 Headers
#include "G4VUserPhysicsList.hh"

// User Headers
#include "LuaInstance.hh"
#include "Utilities.hh"

class ConfigLuaInstance : public LuaInstance {
	
	public:
	
		//for table = Config_Table
		string modulename;
		G4VUserPhysicsList *physicslist;
		
		string DarkGeantOutputFile;
		string DarkGeantOutputLocation;
	
	/*
	 * 
	 * Class member functions
	 * 
	 * */
	public:
	
		ConfigLuaInstance(string ModulePath);
		~ConfigLuaInstance();
		
	private:
	
		//for table = Config_Table
		void Initialize_modulename();
		void Initialize_physicslist();
		
		//for table = DarkGeantOutputFile
		void Initialize_DarkGeantOutputFile();
		void Initialize_DarkGeantOutputLocation();
		
		
	/*
	 * 
	 * TODO
	 * 
	 * Finish class
	 * 
	 * */
	
};

#endif
